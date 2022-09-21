#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

// template<class T>
class ResultDTO : public oatpp::DTO {

  DTO_INIT(ResultDTO, DTO)

  DTO_FIELD(String, message);
  DTO_FIELD_INFO(message){info->description = "信息";}

  DTO_FIELD(Int16, code);
  DTO_FIELD_INFO(code){info->description = "状态码";}

//   DTO_FIELD(T, result);
//   DTO_FIELD_INFO(result){info->description = "结果内容";}

};

#include OATPP_CODEGEN_END(DTO)