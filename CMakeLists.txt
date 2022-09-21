cmake_minimum_required(VERSION 3.2)

set(project_name HIMS)

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

find_package(oatpp REQUIRED)
find_package(oatpp-postgresql REQUIRED)
find_package(oatpp-swagger REQUIRED)

add_library(${project_name}-lib
        "src/AppComponent.h"
        "src/ServiceComponent.h"
        "src/DatabaseComponent.h"
        "src/SwaggerComponent.h"
        "src/ErrorHandler.h"
        "src/ErrorHandler.cpp"

        "src/controller/PatientController.h"

        "src/service/PatientService.h"
        "src/service/PatientService.cpp"

        "src/dtos/PatientDTO.h"
        "src/dtos/ConfigDTO.h"
        "src/dtos/StatusDTO.h"
        "src/dtos/PageDTO.h"
        "src/dtos/ResultDTO.h"

        "src/db/PatientDB.h"
)

add_library(util
        "src/util/empty.cpp"
        "src/util/urlDecode.h"
        )

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-postgresql
        PUBLIC oatpp::oatpp-swagger
)

target_include_directories(${project_name}-lib PUBLIC src)

add_definitions(
        # Path to swagger-ui resources #
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        # Path to config file #
        -DCONFIG_PATH="${PROJECT_SOURCE_DIR}/configuration/config.json"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

add_executable(test_oatpp
        "tests/test_oatpp.cpp")

target_link_libraries(test_oatpp ${project_name}-lib)
add_dependencies(test_oatpp 
        ${project_name}-lib
        util)

