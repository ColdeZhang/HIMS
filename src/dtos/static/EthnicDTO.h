#ifndef ETHNIC_DTO_H
#define ETHNIC_DTO_H

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "../ResultDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace StaticDto{
    class single_ethnic : public oatpp::DTO {
  
      DTO_INIT(single_ethnic, DTO)

      DTO_FIELD(UInt8, id);
      DTO_FIELD(String, ethnic);
      
    };

    class ethnic_list : public ResultDTO{
      DTO_INIT(ethnic_list, ResultDTO)

      DTO_FIELD(oatpp::Vector<oatpp::Object<single_ethnic>>, ethnic_list);
    };
}


#include OATPP_CODEGEN_END(DTO)

#endif /* ETHNIC_DTO_H */