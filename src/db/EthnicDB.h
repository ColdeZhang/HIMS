#ifndef ETHNIC_DB_HPP
#define ETHNIC_DB_HPP

#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * EthnicDB
 * 民族数据库操作语句定义
 */
class EthnicDB : public oatpp::orm::DbClient {
public:

  EthnicDB(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {
        OATPP_LOGD("Initing DB","ethnic")
        auto res_init = executor->execute("CREATE TABLE IF NOT EXISTS ethnics ("
                "id                  int PRIMARY KEY,            " //-- id
                "ethnic              varchar (32) UNIQUE         " //-- 民族
                ");",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (1, '汉')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (2, '蒙古')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (3, '回')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (4, '藏')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (5, '维吾尔')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (6, '苗')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (7, '彝')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (8, '壮')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (9, '布依')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (10, '朝鲜')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (11, '满')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (12, '侗')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (13, '瑶')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (14, '白')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (15, '土家')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (16, '哈尼')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (17, '哈萨克')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (18, '傣')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (19, '黎')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (20, '傈僳')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (21, '佤')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (22, '畲')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (23, '高山')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (24, '拉祜')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (25, '水')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (26, '东乡')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (27, '纳西')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (28, '景颇')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (29, '柯尔克孜')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (30, '土')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (31, '达翰尔')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (32, '么佬')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (33, '羌')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (34, '布朗')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (35, '撒拉')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (36, '毛南')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (37, '仡佬')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (38, '锡伯')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (39, '阿昌')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (40, '普米')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (41, '塔吉克')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (42, '怒')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (43, '乌孜别克')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (44, '俄罗斯')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (45, '鄂温克')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (46, '德昂')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (47, '保安')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (48, '裕固')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (49, '京')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (50, '塔塔尔')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (51, '独龙')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (52, '鄂伦春')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (53, '赫哲')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (54, '门巴')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (55, '珞巴')",{});
        executor->execute("INSERT INTO ethnics (id, ethnic) VALUES (56, '基诺')",{}); 
        OATPP_LOGD("Initing DB", res_init->getErrorMessage().getValue("success").c_str());
        OATPP_LOGD("Initing DB","Done!")
  }

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //ETHNIC_DB_HPP