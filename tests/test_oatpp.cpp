#include "controller/PatientController.h"
#include "AppComponent.h"
#include "DatabaseComponent.h"
#include "ServiceComponent.h"
#include "SwaggerComponent.h"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run(const oatpp::base::CommandLineArguments& args) {

  AppComponent appComponent(args);
  ServiceComponent serviceComponent;
  SwaggerComponent swaggerComponent;
  DatabaseComponent databaseComponent;

  /* create ApiControllers and add endpoints to router */

  auto router = serviceComponent.httpRouter.getObject();
  oatpp::web::server::api::Endpoints docEndpoints;

  auto endpoints = router->addController(PatientController::createShared())->getEndpoints();
  docEndpoints.append(endpoints);

  /* 添加 Swagger 进路由表 */
  router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

  /* create server */

  oatpp::network::Server server(serviceComponent.serverConnectionProvider.getObject(),
                                serviceComponent.serverConnectionHandler.getObject());

  OATPP_LOGD("Server", "Running on port %s...", serviceComponent.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());

  server.run();

}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  run(oatpp::base::CommandLineArguments(argc, argv));

  oatpp::base::Environment::destroy();

  return 0;
}