#ifndef PATIENT_DB_HPP
#define PATIENT_DB_HPP

#include "dtos/PatientDTO.h"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * PatientDb 
 * 病人数据库操作语句定义
 */
class PatientDB : public oatpp::orm::DbClient {
public:

  PatientDB(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {
        executor->execute("CREATE EXTENSION IF NOT EXISTS \"uuid-ossp\";",{});
        OATPP_LOGD("Initing DB","patient_information")
        auto res_patient_information = executor->execute("CREATE TABLE IF NOT EXISTS patient_information ("
                "uuid                varchar (36) PRIMARY KEY UNIQUE ,   " //-- 唯一标识
                "name                varchar (64) NOT NULL ,             " //-- 姓名
                "idn                 varchar (20) NOT NULL UNIQUE ,      " //-- 身份证号码
                "birth               integer NOT NULL ,                  " //-- 出生年月日 YYYYMMDD
                "gender              smallint NOT NULL ,                 " //-- 性别
                "ethnic              smallint NOT NULL ,                 " //-- 民族
                "marital_status      varchar (64) ,                      " //-- 婚姻状况
                "job                 varchar (64) ,                      " //-- 职业
                "company             varchar (128) ,                     " //-- 工作单位
                "address             varchar (256) NOT NULL ,            " //-- 身份证户籍地址
                "address1            varchar (256) NULL ,                " //-- 常住地址
                "phone               varchar (20) NOT NULL ,             " //-- 本人手机/电话
                "phone1              varchar (20) NULL ,                 " //-- 亲属电话/紧急联系人
                "create_time         varchar (128) NOT NULL ,            " //-- 创建时间
                "update_time         varchar (128) NOT NULL ,            " //-- 修改时间
                "is_delete           boolean default false               " //-- 是否被删除
                ");",{});
        OATPP_LOGD("Initing DB", res_patient_information->getErrorMessage().getValue("success").c_str());
        OATPP_LOGD("Initing DB","medical_record")
        auto res_medical_record = executor->execute("CREATE TABLE IF NOT EXISTS outpatient_med_rec ("
                "id                  SERIAL PRIMARY KEY ,                " //-- 自增id（不对外暴露）
                "uuid                varchar (36) NOT NULL ,             " //-- 病历uuid
                "belong_patient      varchar (36) NOT NULL ,             " //-- 病历所属病人（uuid）

                "belong_hospital     varchar (36) NOT NULL ,             " //-- 病历所属医院（uuid）
                "belong_department   varchar (36) NOT NULL ,             " //-- 病历所属科室（uuid）
                "belong_doctor       varchar (36) NOT NULL ,             " //-- 开具病历的医生（uuid）

                "detail              varchar (36) NOT NULL ,             " //-- 病历详情（uuid）

                "versions            integer default 0  ,                " //-- 病历版本
                "create_time         varchar (128) NOT NULL ,            " //-- 此项创建时间

                "examine_doctor      varchar (36),                       " //-- 审批医师（uuid）
                "examine_advice      varchar (256),                      " //-- 审批意见

                "is_archive          boolean default false,              " //-- 是否归档
                "is_delete           boolean default false               " //-- 是否被删除
                ");",{});
        auto res_medical_record_detail = executor->execute("CREATE TABLE IF NOT EXISTS outpatient_med_rec_detail ("
                "uuid                varchar (36) NOT NULL PRIMARY KEY,  " //-- 详情uuid
                "chief_complaint     varchar (256) NOT NULL ,            " //-- 主诉
                "present_illness     varchar (256) NOT NULL ,            " //-- 现病史
                "past_illness        varchar (256) NOT NULL ,            " //-- 既往史
                "allergy_history     varchar (256) NOT NULL ,            " //-- 过敏史
                "family_history      varchar (256) NOT NULL ,            " //-- 家族史
                "physical_examination varchar (256) NOT NULL ,           " //-- 体格检查
                "auxiliary_examination varchar (256) NOT NULL ,          " //-- 辅助检查
                "diagnosis           varchar (256) NOT NULL ,            " //-- 诊断
                "treatment           varchar (256) NOT NULL ,            " //-- 治疗(处理意见)
                "advice              varchar (256) NOT NULL ,            " //-- 医嘱
                ");",{});
        OATPP_LOGD("Initing DB", res_medical_record->getErrorMessage().getValue("success").c_str());
        // hospitalization_med_rec

        OATPP_LOGD("Initing DB","Done!")
  }

  QUERY(createPatient,
        "INSERT INTO patient_information"
        "(uuid, name, idn, birth, gender, ethnic, marital_status, job, company, address, address1, phone, phone1, create_time, update_time) VALUES "
        "(uuid_generate_v4(), :info.name, :info.idn, :info.birth, :info.gender, :info.ethnic, :info.marital_status, :info.job, :info.company,:info.address, :info.address1, :info.phone, :info.phone1, localtimestamp(2), localtimestamp(2))"
        "RETURNING uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::Object<PatientDTO::info_without_uuid_time>, info))

  QUERY(updatePatient,
        "UPDATE patient_information "
        "SET "
            "name = :info.name, "
            "idn = :info.idn, "
            "birth = :info.birth, "
            "gender = :info.gender, "
            "ethnic = :info.ethnic, "
            "marital_status = :info.marital_status, "
            "job = :info.job, "
            "company = :info.company, "
            "address = :info.address, "
            "address1 = :info.address1, "
            "phone = :info.phone, "
            "phone1 =  :info.phone1, "
            "update_time = localtimestamp(2)"
        "WHERE "
        " uuid=:info.uuid "
        "RETURNING uuid, name, idn, birth, gender, ethnic, marital_status, job, company, address, address1, phone, phone1, create_time, update_time;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::Object<PatientDTO::info_with_uuid_no_time>, info))

QUERY(deletePatientByUUID,
        "UPDATE patient_information "
        "SET "
            "is_delete = true, "
            "update_time = localtimestamp(2)"
        "WHERE "
        " uuid=:uuid "
        "RETURNING *;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::String, uuid))

// QUERY(getPatientByIDN,
//         "SELECT * FROM patient_information WHERE idn=:idn and is_delete=false;",
//         PREPARE(true), //<-- prepared statement!
//         PARAM(oatpp::String, idn))
      
QUERY(getPatientByUUID,
        "SELECT "
                "uuid, "
                "name, "
                "idn, "
                "birth, "
                "gender, "
                "ethnic, "
                "marital_status, "
                "job, "
                "company, "
                "address, "
                "address1, "
                "phone, "
                "phone1, "
                "create_time, "
                "update_time "
        "FROM patient_information WHERE uuid=:uuid and is_delete=false;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::String, uuid))

// QUERY(getPatientByName,
//         "SELECT * FROM patient_information WHERE name like :name and is_delete=false;",
//         PREPARE(true), //<-- prepared statement!
//         PARAM(oatpp::String, name))
 
QUERY(getAllPatients,
        "SELECT uuid, name, idn, birth, gender, ethnic, marital_status, job, company, address, address1, phone, phone1, create_time, update_time "
        "FROM patient_information WHERE is_delete=false LIMIT :limit OFFSET :offset;",
        PREPARE(true),
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //PATIENT_DB_HPP