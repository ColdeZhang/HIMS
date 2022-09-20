#ifndef PatientDTO_hpp
#define PatientDTO_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "ResultDTO.h"
#include "PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace PatientDTO
{

  // 患者信息 不包含 UUID 时间戳（用于创建）
  class CREATE : public oatpp::DTO {
    
    DTO_INIT(CREATE, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name){info->description = "姓名";}

    DTO_FIELD(String, idn);
    DTO_FIELD_INFO(idn){info->description = "身份证号";}

    DTO_FIELD(Int32, birth);
    DTO_FIELD_INFO(birth){info->description = "出生日期 格式 YYYYMMDD";}

    DTO_FIELD(Int8, gender);
    DTO_FIELD_INFO(gender){info->description = "性别";}

    DTO_FIELD(String, ethnic);
    DTO_FIELD_INFO(ethnic){info->description = "民族";}

    DTO_FIELD(String, address);
    DTO_FIELD_INFO(address){info->description = "户籍住址";}

    DTO_FIELD(String, address1);
    DTO_FIELD_INFO(address1){info->description = "常住地址";}

    DTO_FIELD(String, phone);
    DTO_FIELD_INFO(phone){info->description = "本人电话";}

    DTO_FIELD(String, phone1);
    DTO_FIELD_INFO(phone1){info->description = "亲属电话";}

  };

 // 患者信息 包含 UUID 不包含 时间戳（用于更新）
  class SET : public CREATE {
    
    DTO_INIT(SET, CREATE)

    DTO_FIELD(String, uuid);
    DTO_FIELD_INFO(uuid){info->description = "主键uuid 唯一标识";}
  };


  // 患者信息 包含 UUID 时间戳（用于获取）
  class GET : public SET {
    
    DTO_INIT(GET, SET)

    DTO_FIELD(String, create_time);
    DTO_FIELD_INFO(create_time){info->description = "创建时间";}

    DTO_FIELD(String, update_time);
    DTO_FIELD_INFO(update_time){info->description = "修改时间";}
  };

  // 分页body
  class Page : public PageDTO<oatpp::Object<PatientDTO::GET>>{
    DTO_INIT(Page, PageDTO<oatpp::Object<PatientDTO::GET>>)
  };
  // 用于分页批量获取患者
  class PageResult : public ResultDTO {
    DTO_INIT(PageResult, ResultDTO)
    DTO_FIELD(oatpp::Object<Page>, result);
  };
  // 创建患者后返回新患者的信息
  class SingleResult : public ResultDTO {
    DTO_INIT(SingleResult, ResultDTO)
    DTO_FIELD(oatpp::Object<GET>, result);
  };
  // 符合条件的多个患者信息
  class MultiResults : public ResultDTO {
    DTO_INIT(MultiResults, ResultDTO)
    DTO_FIELD(oatpp::Vector<oatpp::Object<GET>>, result);
  };
  // 不包含患者信息的结果
  class JustResult : public ResultDTO {
    DTO_INIT(JustResult, ResultDTO)
  };



} // namespace PatientDTO






#include OATPP_CODEGEN_END(DTO)

#endif /* PatientDTO_hppp */