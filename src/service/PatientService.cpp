
#include "PatientService.h"
#include "../util/urlDecode.h"

oatpp::Object<PatientDTO::result_with_single> PatientService::createPatient(const oatpp::Object<PatientDTO::info_without_uuid_time>& dto) {
  auto res = PatientDTO::result_with_single::createShared();
  auto dbResult = m_database->createPatient(dto);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::info_with_uuid_time>>>();
  if (result->size() != 1){
    res->code = 500;
    res->message = "内部错误";
    return res;
  }
  res->code = 200;
  res->message = "success";
  res->result = result[0];
  return res;
}

oatpp::Object<PatientDTO::result_with_single> PatientService::updatePatient(const oatpp::Object<PatientDTO::info_with_uuid_no_time>& dto) {
  auto res = PatientDTO::result_with_single::createShared();
  auto dbResult = m_database->updatePatient(dto);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::info_with_uuid_time>>>();
  if (result->size() != 1){
    res->code = 500;
    res->message = "内部错误";
    return res;
  }
  res->code = 200;
  res->message = "success";
  res->result = result[0];
  return res;
}

oatpp::Object<PatientDTO::result_with_multi> PatientService::getPatientsByIDN(const oatpp::String& idn) {
  auto res = PatientDTO::result_with_multi::createShared();
  auto dbResult = m_database->executeQuery("SELECT uuid, name, idn, birth, gender, ethnic, marital_status, job, company, address, address1, phone, phone1, create_time, update_time  FROM patient_information WHERE idn like '%"+idn+"%' AND is_delete=false LIMIT 5;",{});
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::info_with_uuid_time>>>();
  res->code = 200;
  res->message = "success";
  res->result = result;
  return res;
}

oatpp::Object<PatientDTO::result_with_multi> PatientService::getPatientsByName(const oatpp::String& name) {
  auto res = PatientDTO::result_with_multi::createShared();
  // 对name进行utf-8编码
  oatpp::String _name = util::acl_url_decode(name->c_str());
  auto dbResult = m_database->executeQuery("SELECT uuid, name, idn, birth, gender, ethnic, marital_status, job, company, address, address1, phone, phone1, create_time, update_time  FROM patient_information WHERE name like '%"+_name+"%' AND is_delete=false LIMIT 5;",{});
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::info_with_uuid_time>>>();
  res->code = 200;
  res->message = "success";
  res->result = result;
  return res;
}

oatpp::Object<PatientDTO::result_with_single> PatientService::getPatientByUUID(const oatpp::String& uuid) {
  auto res = PatientDTO::result_with_single::createShared();
  auto dbResult = m_database->getPatientByUUID(uuid);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::info_with_uuid_time>>>();
  if (result->size() != 1){
    res->code = 500;
    res->message = "内部错误";
    return res;
  }
  res->code = 200;
  res->message = "success";
  res->result = result[0];
  return res;
}

oatpp::Object<PatientDTO::result_with_page> PatientService::getAllPatients(const oatpp::UInt32& page, const oatpp::UInt32& eachPage) {
  auto res = PatientDTO::result_with_page::createShared();
  oatpp::UInt32 offset = eachPage * (page - 1);
  oatpp::UInt32 limit = eachPage;
  auto dbResult = m_database->getAllPatients(offset, limit);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::info_with_uuid_time>>>();
  res->code = 200;
  res->message = "success";

  auto page_res  = PatientDTO::page_with_info::createShared();
  page_res->page = page;
  page_res->eachPage = eachPage;
  page_res->totalPage = 99;
  page_res->items = items;

  res->result = page_res;

  return res;
}

oatpp::Object<PatientDTO::result_with_nothing> PatientService::deletePatientByUUID(const oatpp::String& uuid) {
  auto res = PatientDTO::result_with_nothing::createShared();
  auto dbResult = m_database->deletePatientByUUID(uuid);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  res->code = 200;
  res->message = "success";
  return res;
}