
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

  oatpp::Object<PatientDTO::SingleResult> createPatient(const oatpp::Object<PatientDTO::CREATE>& dto);
  oatpp::Object<PatientDTO::SingleResult> updatePatient(const oatpp::Object<PatientDTO::SET>& dto);
  oatpp::Object<PatientDTO::SingleResult> getPatientByUUID(const oatpp::String& uuid);

  oatpp::Object<PatientDTO::MultiResults> getPatientsByIDN(const oatpp::String& idn);
  oatpp::Object<PatientDTO::MultiResults> getPatientsByName(const oatpp::String& name);

  oatpp::Object<PatientDTO::PageResult> getAllPatients(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  
  oatpp::Object<PatientDTO::JustResult> deletePatientByUUID(const oatpp::String& uuid);

};

#endif //EXAMPLE_POSTGRESQL_USERSERVICE_HPP
