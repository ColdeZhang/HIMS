
#ifndef EXAMPLE_POSTGRESQL_PAGEDTO_HPP
#define EXAMPLE_POSTGRESQL_PAGEDTO_HPP

#include "PatientDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDTO : public oatpp::DTO {

  DTO_INIT(PageDTO, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD_INFO(offset){info->description = "偏移量";}
  DTO_FIELD(UInt32, limit);
  DTO_FIELD_INFO(limit){info->description = "每页数量";}
  DTO_FIELD(UInt32, count);
  DTO_FIELD_INFO(count){info->description = "总页数";}
  DTO_FIELD(Vector<T>, items);

};

#include OATPP_CODEGEN_END(DTO)

#endif //EXAMPLE_POSTGRESQL_PAGEDTO_HPP
