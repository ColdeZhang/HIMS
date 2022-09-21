
#include "PatientService.h"
#include "../util/urlDecode.h"

oatpp::Object<PatientDTO::SingleResult> PatientService::createPatient(const oatpp::Object<PatientDTO::CREATE>& dto) {
  auto res = PatientDTO::SingleResult::createShared();
  auto dbResult = m_database->createPatient(dto);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::GET>>>();
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

oatpp::Object<PatientDTO::SingleResult> PatientService::updatePatient(const oatpp::Object<PatientDTO::SET>& dto) {
  auto res = PatientDTO::SingleResult::createShared();
  auto dbResult = m_database->updatePatient(dto);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::GET>>>();
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

oatpp::Object<PatientDTO::MultiResults> PatientService::getPatientsByIDN(const oatpp::String& idn) {
  auto res = PatientDTO::MultiResults::createShared();
  auto dbResult = m_database->executeQuery("SELECT uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time  FROM patient_information WHERE idn like '%"+idn+"%' AND is_delete=false LIMIT 5;",{});
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::GET>>>();
  res->code = 200;
  res->message = "success";
  res->result = result;
  return res;
}

oatpp::Object<PatientDTO::MultiResults> PatientService::getPatientsByName(const oatpp::String& name) {
  auto res = PatientDTO::MultiResults::createShared();
  // 对name进行utf-8编码
  oatpp::String _name = util::acl_url_decode(name->c_str());
  auto dbResult = m_database->executeQuery("SELECT uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time  FROM patient_information WHERE name like '%"+_name+"%' AND is_delete=false LIMIT 5;",{});
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::GET>>>();
  res->code = 200;
  res->message = "success";
  res->result = result;
  return res;
}

oatpp::Object<PatientDTO::SingleResult> PatientService::getPatientByUUID(const oatpp::String& uuid) {
  auto res = PatientDTO::SingleResult::createShared();
  auto dbResult = m_database->getPatientByUUID(uuid);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::GET>>>();
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

oatpp::Object<PatientDTO::PageResult> PatientService::getAllPatients(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
  auto res = PatientDTO::PageResult::createShared();
  auto dbResult = m_database->getAllPatients(offset, limit);
  if (!dbResult->isSuccess()){
    res->code = 500;
    res->message = dbResult->getErrorMessage();
    return res;
  }
  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<PatientDTO::GET>>>();
  res->code = 200;
  res->message = "success";

  auto page  = PatientDTO::Page::createShared();
  page->offset = offset;
  page->limit = limit;
  page->items = items;
  page->count = 99;
  res->result = page;

  return res;
}

oatpp::Object<PatientDTO::JustResult> PatientService::deletePatientByUUID(const oatpp::String& uuid) {
  auto res = PatientDTO::JustResult::createShared();
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