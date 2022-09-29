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
  class info_without_uuid_time : public oatpp::DTO {
    
    DTO_INIT(info_without_uuid_time, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name){info->description = "姓名";}

    DTO_FIELD(String, idn);
    DTO_FIELD_INFO(idn){info->description = "身份证号";}

    DTO_FIELD(Int16, birth);
    DTO_FIELD_INFO(birth){info->description = "出生日期 格式 YYYYMMDD";}

    DTO_FIELD(Int8, gender);
    DTO_FIELD_INFO(gender){info->description = "性别";}

    DTO_FIELD(Int8, ethnic);
    DTO_FIELD_INFO(ethnic){info->description = "民族";}

    DTO_FIELD(String, marital_status);
    DTO_FIELD_INFO(marital_status){info->description = "婚姻状况";}

    DTO_FIELD(String, job);
    DTO_FIELD_INFO(job){info->description = "工作";}

    DTO_FIELD(String, company);
    DTO_FIELD_INFO(company){info->description = "工作单位";}

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
  class info_with_uuid_no_time : public info_without_uuid_time {
    
    DTO_INIT(info_with_uuid_no_time, info_without_uuid_time)

    DTO_FIELD(String, uuid);
    DTO_FIELD_INFO(uuid){info->description = "主键uuid 唯一标识";}
  };


  // 患者信息 包含 UUID 时间戳（用于获取）
  class info_with_uuid_time : public info_with_uuid_no_time {
    
    DTO_INIT(info_with_uuid_time, info_with_uuid_no_time)

    DTO_FIELD(String, create_time);
    DTO_FIELD_INFO(create_time){info->description = "创建时间";}

    DTO_FIELD(String, update_time);
    DTO_FIELD_INFO(update_time){info->description = "修改时间";}
  };

  // 分页body
  class page_with_info : public PageDTO<oatpp::Object<PatientDTO::info_with_uuid_time>>{
    DTO_INIT(page_with_info, PageDTO<oatpp::Object<PatientDTO::info_with_uuid_time>>)
  };
  // 用于分页批量获取患者
  class result_with_page : public ResultDTO {
    DTO_INIT(result_with_page, ResultDTO)
    DTO_FIELD(oatpp::Object<page_with_info>, result);
  };
  // 创建患者后返回新患者的信息
  class result_with_single : public ResultDTO {
    DTO_INIT(result_with_single, ResultDTO)
    DTO_FIELD(oatpp::Object<info_with_uuid_time>, result);
  };
  // 符合条件的多个患者信息
  class result_with_multi : public ResultDTO {
    DTO_INIT(result_with_multi, ResultDTO)
    DTO_FIELD(oatpp::Vector<oatpp::Object<info_with_uuid_time>>, result);
  };
  // 不包含患者信息的结果
  class result_with_nothing : public ResultDTO {
    DTO_INIT(result_with_nothing, ResultDTO)
  };



} // namespace PatientDTO






#include OATPP_CODEGEN_END(DTO)

#endif /* PatientDTO_hppp */