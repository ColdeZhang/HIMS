
#ifndef STATIC_CONTROLLER_H
#define STATIC_CONTROLLER_H

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "../dtos/static/EthnicDTO.h"
#include "../db/EthnicDB.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class StaticController : public oatpp::web::server::api::ApiController {
public:
  StaticController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}

private:
  OATPP_COMPONENT(std::shared_ptr<EthnicDB>, m_database);

public:

  static std::shared_ptr<StaticController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)){
    return std::make_shared<StaticController>(objectMapper);
  }
  
  ENDPOINT_INFO(getEthnicList) {
    info->summary = "获取民族列表";
    info->addResponse<Object<StaticDto::ethnic_list>>(Status::CODE_200, "application/json");
    info->addTag("常量数据");
  }
  ENDPOINT("GET", "static/ethnic", getEthnicList)
  {
    auto res = StaticDto::ethnic_list::createShared();
    auto dbResult = m_database->getEthnicList();
    res->ethnic_list = dbResult->fetch<oatpp::Vector<oatpp::Object<StaticDto::single_ethnic>>>();
    res->code = 200;
    res->message = "success";
    return createDtoResponse(Status::CODE_200, res);
  }



  ADD_CORS(getEthnicList)
  
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* STATIC_CONTROLLER_H */
