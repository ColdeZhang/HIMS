
#ifndef PatientController_hpp
#define PatientController_hpp

#include "service/PatientService.h"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class PatientController : public oatpp::web::server::api::ApiController {
public:
  PatientController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  PatientService m_patientService; // Create user service.
public:

  static std::shared_ptr<PatientController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<PatientController>(objectMapper);
  }
  
  ENDPOINT_INFO(createPatient) {
    info->summary = "创建患者信息";
    info->addConsumes<Object<PatientDTO::info_without_uuid_time>>("application/json");
    info->addResponse<Object<PatientDTO::info_with_uuid_time>>(Status::CODE_200, "application/json");
    info->addTag("患者信息");
  }
  ENDPOINT("POST", "patient", createPatient, BODY_DTO(Object<PatientDTO::info_without_uuid_time>, dto))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.createPatient(dto));
  }
  
  
  ENDPOINT_INFO(updatePatient) {
    info->summary = "依据uuid更新患者信息";
    info->addConsumes<Object<PatientDTO::info_with_uuid_no_time>>("application/json");
    info->addResponse<Object<PatientDTO::info_with_uuid_time>>(Status::CODE_200, "application/json");
    info->pathParams["uuid"].description = "患者UUID";
    info->addTag("患者信息");
  }
  ENDPOINT("PUT", "patient", updatePatient,
           BODY_DTO(Object<PatientDTO::info_with_uuid_no_time>, dot))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.updatePatient(dot));
  }
  
  
  ENDPOINT_INFO(getPatientByUUID) {
    info->summary = "根据uuid获取患者信息";
    info->addResponse<Object<PatientDTO::info_with_uuid_time>>(Status::CODE_200, "application/json");
    info->pathParams["uuid"].description = "患者UUID";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/byUuid", getPatientByUUID,
           QUERY(String, uuid))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getPatientByUUID(uuid));
  }

  ENDPOINT_INFO(getPatientByIDN) {
    info->summary = "根据身份证号模糊获取多个患者信息 - 最多5条";
    info->addResponse<Object<PatientDTO::result_with_multi>>(Status::CODE_200, "application/json");
    info->pathParams["idn"].description = "患者身份证号";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/byIdn", getPatientByIDN,
           QUERY(String, idn))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getPatientsByIDN(idn));
  }

  ENDPOINT_INFO(getPatientByName) {
    info->summary = "根据姓名模糊获取患者信息 - 最多5条";
    info->addResponse<Object<PatientDTO::result_with_multi>>(Status::CODE_200, "application/json");
    info->pathParams["name"].description = "患者姓名";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/byName", getPatientByName,
           QUERY(String, name))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getPatientsByName(name));
  }

  ENDPOINT_INFO(getAllPatients) {
    info->summary = "获取所有患者信息";
    info->addResponse<Object<PatientDTO::result_with_page>>(Status::CODE_200, "application/json");
    info->pathParams["page"].description = "页码";
    info->pathParams["eachPage"].description = "每页数量";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/page", getAllPatients,
           QUERY(oatpp::UInt32, page),
           QUERY(oatpp::UInt32, totalPage))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getAllPatients(page, totalPage));
  }


  ENDPOINT_INFO(deletePatient) {
    info->summary = "根据uuid删除患者信息";
    info->addResponse<Object<PatientDTO::result_with_nothing>>(Status::CODE_200, "application/json");
    info->pathParams["uuid"].description = "患者UUID";
    info->addTag("患者信息");
  }
  ENDPOINT("DELETE", "patient", deletePatient,
           QUERY(String, uuid))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.deletePatientByUUID(uuid));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* PatientController_hpp */
