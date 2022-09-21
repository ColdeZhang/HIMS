
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
    info->addConsumes<Object<PatientDTO::CREATE>>("application/json");
    info->addResponse<Object<PatientDTO::GET>>(Status::CODE_200, "application/json");
    info->addTag("患者信息");
  }
  ENDPOINT("POST", "patient", createPatient, BODY_DTO(Object<PatientDTO::CREATE>, dto))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.createPatient(dto));
  }
  
  
  ENDPOINT_INFO(updatePatient) {
    info->summary = "依据uuid更新患者信息";
    info->addConsumes<Object<PatientDTO::SET>>("application/json");
    info->addResponse<Object<PatientDTO::GET>>(Status::CODE_200, "application/json");
    info->pathParams["uuid"].description = "患者UUID";
    info->addTag("患者信息");
  }
  ENDPOINT("PUT", "patient", updatePatient,
           BODY_DTO(Object<PatientDTO::SET>, dot))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.updatePatient(dot));
  }
  
  
  ENDPOINT_INFO(getPatientByUUID) {
    info->summary = "根据uuid获取患者信息";
    info->addResponse<Object<PatientDTO::GET>>(Status::CODE_200, "application/json");
    info->pathParams["uuid"].description = "患者UUID";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/uuid/{uuid}", getPatientByUUID,
           PATH(String, uuid))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getPatientByUUID(uuid));
  }

  ENDPOINT_INFO(getPatientByIDN) {
    info->summary = "根据身份证号获取患者信息";
    info->addResponse<Object<PatientDTO::MultiResults>>(Status::CODE_200, "application/json");
    info->pathParams["idn"].description = "患者身份证号";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/idn/{idn}", getPatientByIDN,
           PATH(String, idn))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getPatientsByIDN(idn));
  }

  ENDPOINT_INFO(getPatientByName) {
    info->summary = "根据姓名获取患者信息";
    info->addResponse<Object<PatientDTO::MultiResults>>(Status::CODE_200, "application/json");
    info->pathParams["name"].description = "患者姓名";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/name/", getPatientByName,
           QUERY(String, name))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getPatientsByName(name));
  }

  ENDPOINT_INFO(getAllPatients) {
    info->summary = "获取所有患者信息";
    info->addResponse<Object<PatientDTO::PageResult>>(Status::CODE_200, "application/json");
    info->pathParams["offset"].description = "偏移量";
    info->pathParams["limit"].description = "每页数量";
    info->addTag("患者信息");
  }
  ENDPOINT("GET", "patient/page/{offset}/{limit}", getAllPatients,
           PATH(oatpp::UInt32, offset),
           PATH(oatpp::UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.getAllPatients(offset, limit));
  }


  ENDPOINT_INFO(deletePatient) {
    info->summary = "根据uuid删除患者信息";
    info->addResponse<Object<PatientDTO::JustResult>>(Status::CODE_200, "application/json");
    info->pathParams["uuid"].description = "患者UUID";
    info->addTag("患者信息");
  }
  ENDPOINT("DELETE", "patient/{uuid}", deletePatient,
           PATH(String, uuid))
  {
    return createDtoResponse(Status::CODE_200, m_patientService.deletePatientByUUID(uuid));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* PatientController_hpp */
