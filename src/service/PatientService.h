
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

  oatpp::Object<PatientInformationDTO> createUser(const oatpp::Object<PatientInformationDTO>& dto);
  oatpp::Object<PatientInformationDTO> updateUser(const oatpp::Object<PatientInformationDTO>& dto);
  oatpp::Object<PatientInformationDTO> getUserById(const oatpp::String& id);
  oatpp::Object<PageDto<oatpp::Object<PatientInformationDTO>>> getAllUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deleteUserById(const oatpp::String& id);

};

#endif //EXAMPLE_POSTGRESQL_USERSERVICE_HPP
