
#ifndef EXAMPLE_POSTGRESQL_PAGEDTO_HPP
#define EXAMPLE_POSTGRESQL_PAGEDTO_HPP

#include "PatientInformationDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDTO : public oatpp::DTO {

  DTO_INIT(PageDTO, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD(UInt32, limit);
  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class UsersPageDto : public PageDto<oatpp::Object<PatientInformationDTO>> {

  DTO_INIT(UsersPageDto, PageDto<oatpp::Object<PatientInformationDTO>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif //EXAMPLE_POSTGRESQL_PAGEDTO_HPP
