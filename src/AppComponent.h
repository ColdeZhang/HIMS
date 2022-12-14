#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "dtos/ConfigDTO.h"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"

#include <cstdlib>

class AppComponent {
private:
  oatpp::base::CommandLineArguments m_cmdArgs;
public:
  AppComponent(const oatpp::base::CommandLineArguments& cmdArgs)
    : m_cmdArgs(cmdArgs)
  {}
public:
  
  /**
   * 配置组件加载、注册
   */
  OATPP_CREATE_COMPONENT(oatpp::Object<ConfigDTO>, config)([this] {

    const char* configPath = CONFIG_PATH;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    
    oatpp::String configText = oatpp::String::loadFromFile(configPath);
    if (configText) {

      auto profiles = objectMapper->readFromString<oatpp::Fields<oatpp::Object<ConfigDTO>>>(configText);

      const char *profileArg = std::getenv("CONFIG_PROFILE"); // first read from env variable
      if (profileArg == nullptr) {
        profileArg = m_cmdArgs.getNamedArgumentValue("--profile", "dev"); // if no env varioable get from command line
      }

      OATPP_LOGD("Server", "开始加载配置文件项： '%s'", profileArg);

      auto profile = profiles.getValueByKey(profileArg, nullptr);
      if(!profile) {
        throw std::runtime_error("配置项无效，服务器终止启动。");
      }
      return profile;
      
    }
    
    OATPP_LOGE("Server", "无法加载配置文件： '%s'", configPath);
    throw std::runtime_error("[AppComponent]: Can't load configuration file");
    
  }());
  
};

#endif /* AppComponent_hpp */