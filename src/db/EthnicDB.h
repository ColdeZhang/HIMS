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
                "value              int PRIMARY KEY,            " //-- value
                "label              varchar (32) UNIQUE         " //-- 民族
                ");",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (1, '汉')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (2, '蒙古')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (3, '回')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (4, '藏')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (5, '维吾尔')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (6, '苗')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (7, '彝')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (8, '壮')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (9, '布依')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (10, '朝鲜')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (11, '满')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (12, '侗')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (13, '瑶')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (14, '白')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (15, '土家')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (16, '哈尼')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (17, '哈萨克')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (18, '傣')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (19, '黎')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (20, '傈僳')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (21, '佤')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (22, '畲')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (23, '高山')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (24, '拉祜')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (25, '水')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (26, '东乡')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (27, '纳西')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (28, '景颇')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (29, '柯尔克孜')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (30, '土')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (31, '达翰尔')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (32, '么佬')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (33, '羌')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (34, '布朗')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (35, '撒拉')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (36, '毛南')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (37, '仡佬')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (38, '锡伯')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (39, '阿昌')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (40, '普米')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (41, '塔吉克')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (42, '怒')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (43, '乌孜别克')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (44, '俄罗斯')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (45, '鄂温克')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (46, '德昂')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (47, '保安')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (48, '裕固')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (49, '京')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (50, '塔塔尔')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (51, '独龙')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (52, '鄂伦春')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (53, '赫哲')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (54, '门巴')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (55, '珞巴')",{});
        executor->execute("INSERT INTO ethnics (value, label) VALUES (56, '基诺')",{}); 
        OATPP_LOGD("Initing DB", res_init->getErrorMessage().getValue("success").c_str());
        OATPP_LOGD("Initing DB","Done!")
  }

  QUERY(getEthnicList,
        "SELECT * FROM ethnics;",
        PREPARE(true)) //<-- prepared statement!

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //ETHNIC_DB_HPP