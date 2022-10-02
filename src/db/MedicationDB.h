#ifndef MEDICATION_DB_H
#define MEDICATION_DB_H

#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen


/**
 * @brief 病历数据库
 * 
 */
class MedicationDB : public oatpp::orm::DbClient {
public:

  MedicationDB(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {


    
  }


}

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif // MEDICATION_DB_H