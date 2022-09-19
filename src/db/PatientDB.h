#ifndef EXAMPLE_POSTGRESQL_USERDB_HPP
#define EXAMPLE_POSTGRESQL_USERDB_HPP

#include "dtos/PatientInformationDTO.h"
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
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("PatientDB", "Migration - OK. Version=%d.", version);

  }

  QUERY(createPatient,
        "INSERT INTO patient_information"
        "(uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time) VALUES "
        "(uuid_generate_v4(), :info.name, :info.idn, :info.gender, :info.ethnic, :info.address, :info.address1, :info.phone, :info.phone1, current_timestamp(2), current_timestamp(2))"
        "RETURNING *;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::Object<PatientInformationDTO>, info))

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
            "update_time = current_timestamp(2)"
        "WHERE "
        " id=:info.id "
        "RETURNING *;",
        PREPARE(true), //<-- prepared statement!
        PARAM(oatpp::Object<PatientInformationDTO>, info))

//   QUERY(getUserById,
//         "SELECT * FROM AppUser WHERE id=:id;",
//         PREPARE(true), //<-- user prepared statement!
//         PARAM(oatpp::String, id))

//   QUERY(getAllUsers,
//         "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
//         PREPARE(true), //<-- user prepared statement!
//         PARAM(oatpp::UInt32, offset),
//         PARAM(oatpp::UInt32, limit))

//   QUERY(deleteUserById,
//         "DELETE FROM AppUser WHERE id=:id;",
//         PREPARE(true), //<-- user prepared statement!
//         PARAM(oatpp::String, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //EXAMPLE_POSTGRESQL_USERDB_HPP