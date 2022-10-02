# OHIMS
采用c++编写的医院信息管理系统（Open Hospital Information Manage System）。

后端使用Oat++框架，PostgreSQL数据库。

```
|- CMakeLists.txt                        // 项目配置 CMakeLists.txt
|- src/
|    |
|    |- controller/                      // http 接口与路由注册 swagger文档信息
|    |- db/                              // 数据库访问接口、语句
|    |- dtos/                            // DTO 文件存放目录
|    |- service/                         // 接口功能逻辑实现
|    |- ServiceComponent.hpp             // Service 配置 (端口, ObjectMapper, 数据库)
|    |- SwaggerComponent.hpp             // swagger-ui 配置
|    |- AppComponent.hpp                 // App组件（主要负责加载配置）
|    |- DatabaseComponent.hpp            // 数据库组件、配置
|    |- App.cpp                          // main() 主函数
|    
|- tests/                                // 测试文件存放
|- utility/                              // 部署脚本、工具等
|- configuration/config.json             // 配置文件存放
|- web/                                  // 前端
```