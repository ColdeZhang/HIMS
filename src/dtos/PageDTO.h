
#ifndef EXAMPLE_POSTGRESQL_PAGEDTO_HPP
#define EXAMPLE_POSTGRESQL_PAGEDTO_HPP

#include "PatientDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDTO : public oatpp::DTO {

  DTO_INIT(PageDTO, DTO)

  DTO_FIELD(UInt32, page);
  DTO_FIELD_INFO(page){info->description = "页码";}
  
  DTO_FIELD(UInt32, eachPage);
  DTO_FIELD_INFO(eachPage){info->description = "每页数量";}

  DTO_FIELD(UInt32, totalPage);
  DTO_FIELD_INFO(totalPage){info->description = "总页数";}

  DTO_FIELD(Vector<T>, items);

};

#include OATPP_CODEGEN_END(DTO)

#endif //EXAMPLE_POSTGRESQL_PAGEDTO_HPP
