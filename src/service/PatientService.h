
#ifndef EXAMPLE_POSTGRESQL_USERSERVICE_HPP
#define EXAMPLE_POSTGRESQL_USERSERVICE_HPP

#include "db/PatientDB.h"
#include "dtos/PageDTO.h"
#include "dtos/StatusDTO.h"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class PatientService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<PatientDB>, m_database); // Inject database component
public:

  oatpp::Object<PatientDTO::result_with_single> createPatient(const oatpp::Object<PatientDTO::info_without_uuid_time>& dto);
  oatpp::Object<PatientDTO::result_with_single> updatePatient(const oatpp::Object<PatientDTO::info_with_uuid_no_time>& dto);
  oatpp::Object<PatientDTO::result_with_single> getPatientByUUID(const oatpp::String& uuid);

  oatpp::Object<PatientDTO::result_with_multi> getPatientsByIDN(const oatpp::String& idn);
  oatpp::Object<PatientDTO::result_with_multi> getPatientsByName(const oatpp::String& name);

  oatpp::Object<PatientDTO::result_with_page> getAllPatients(const oatpp::UInt32& page, const oatpp::UInt32& eachPage);
  
  oatpp::Object<PatientDTO::result_with_nothing> deletePatientByUUID(const oatpp::String& uuid);

};

#endif //EXAMPLE_POSTGRESQL_USERSERVICE_HPP
