
#ifndef EXAMPLE_POSTGRESQL_DATABASECOMPONENT_HPP
#define EXAMPLE_POSTGRESQL_DATABASECOMPONENT_HPP

#include "db/PatientDB.h"
#include "dtos/ConfigDTO.h"

class DatabaseComponent {
public:

  /**
   * Create database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<PatientDB>, userDb)([] {

    OATPP_COMPONENT(oatpp::Object<ConfigDto>, config); // Get config component

    /* Create database-specific ConnectionProvider */
    auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(config->dbConnectionString);

    /* Create database-specific ConnectionPool */
    auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                          100 /* max-connections */,
                                                                          std::chrono::seconds(5) /* connection TTL */);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

    /* Create MyClient database client */
    return std::make_shared<UserDb>(executor);

  }());


};

#endif //EXAMPLE_POSTGRESQL_DATABASECOMPONENT_HPP
