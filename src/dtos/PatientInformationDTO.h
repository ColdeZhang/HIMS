#ifndef PatientrDTO_hpp
#define PatientrDTO_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(GENDER, v_uint8,
     VALUE(FEMALE, 0, "FEMALE"),
     VALUE(MALE, 1, "MALE")
)

class PatientInformationDTO : public oatpp::DTO {
  
  DTO_INIT(PatientInformationDTO, DTO)

  DTO_FIELD(String, uuid);
  DTO_FIELD_INFO(uuid){info->description = "主键uuid 唯一标识";}

  DTO_FIELD(String, name);
  DTO_FIELD_INFO(name){info->description = "姓名";}

  DTO_FIELD(String, idn);
  DTO_FIELD_INFO(idn){info->description = "身份证号";}

  DTO_FIELD(Int16, birth);
  DTO_FIELD_INFO(birth){info->description = "出生日期 格式 YYYYMMDD";}

  DTO_FIELD(Enum<GENDER>::AsNumber, gender);
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

  DTO_FIELD(Int64, create_time);
  DTO_FIELD_INFO(create_time){info->description = "创建时间";}

  DTO_FIELD(Int64, update_time);
  DTO_FIELD_INFO(update_time){info->description = "更新时间";}

  DTO_FIELD(Boolean, is_delete) = false;
  DTO_FIELD_INFO(is_delete){info->description = "是否删除";}

};

#include OATPP_CODEGEN_END(DTO)

#endif /* PatientrDTO_hppp */