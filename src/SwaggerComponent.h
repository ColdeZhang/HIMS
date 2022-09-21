#ifndef SwaggerComponent_hpp
#define SwaggerComponent_hpp

#include "dtos/ConfigDTO.h"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "oatpp/core/macro/component.hpp"

class SwaggerComponent {
public:
  
  /**
   *  General API docs info
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
    OATPP_COMPONENT(oatpp::Object<ConfigDTO>, config); // Get config component
    
    oatpp::swagger::DocumentInfo::Builder builder;
    
    builder
    .setTitle("HIMS - API")
    .setDescription("Hospital Information Manage System backend api documentation.")
    .setVersion("1.0")
    .setContactName("Deer")
    .setContactUrl("https://blog.deercloud.site/")
    
    .addServer("http://" + config->swaggerHost, "server on localhost");
    
    return builder.build();
    
  }());
  
  
  /**
   *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
    // Make sure to specify correct full path to oatpp-swagger/res folder !!!
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());
  
};

#endif /* SwaggerComponent_hpp */
