#ifndef EXAMPLE_POSTGRESQL_USERDB_HPP
#define EXAMPLE_POSTGRESQL_USERDB_HPP

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

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/patient_db_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("PatientDB", "Migration - OK. Version=%d.", version);

  }

  QUERY(createPatient,
        "INSERT INTO patient_information"
        "(uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time) VALUES "
        "(uuid_generate_v4(), :info.name, :info.idn, :info.birth, :info.gender, :info.ethnic, :info.address, :info.address1, :info.phone, :info.phone1, localtimestamp(2), localtimestamp(2))"
        "RETURNING uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::Object<PatientDTO::CREATE>, info))

  QUERY(updatePatient,
        "UPDATE patient_information "
        "SET "
            "name = :info.name, "
            "idn = :info.idn, "
            "birth = :info.birth, "
            "gender = :info.gender, "
            "ethnic = :info.ethnic, "
            "address = :info.address, "
            "address1 = :info.address1, "
            "phone = :info.phone, "
            "phone1 =  :info.phone1, "
            "update_time = localtimestamp(2)"
        "WHERE "
        " uuid=:info.uuid "
        "RETURNING uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::Object<PatientDTO::SET>, info))

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

QUERY(getPatientByIDN,
        "SELECT * FROM patient_information WHERE idn=:idn and is_delete=false;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::String, idn))
      
QUERY(getPatientByUUID,
        "SELECT * FROM patient_information WHERE uuid=:uuid and is_delete=false;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::String, uuid))

QUERY(getPatientByName,
        "SELECT * FROM patient_information WHERE name=:name and is_delete=false;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::String, name))

QUERY(getAllPatients,
        "SELECT uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time "
        "FROM patient_information WHERE is_delete=false LIMIT :limit OFFSET :offset;",
        PREPARE(true),
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //EXAMPLE_POSTGRESQL_USERDB_HPP