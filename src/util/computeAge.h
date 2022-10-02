#pragma once

#include <ctime>

namespace util{
    /**
     * @brief 根据出生年月日计算年龄 精确到月份
     * @param y 出生年
     * @param m 出生月
     * @param d 出生日
     * @param age_y 年龄（岁）
     * @param age_m 年龄（月）
     */
    void getAge(int y, int m, int d, int &age_y, int &age_m){
        time_t now;
        time(&now);
        struct tm *tm_now = localtime(&now);
        int now_y = tm_now->tm_year + 1900;
        int now_m = tm_now->tm_mon + 1;
        int now_d = tm_now->tm_mday;

        age_y = now_y - y;
        age_m = now_m - m;
        if (age_m < 0) {
            age_y--;
            age_m += 12;
        }
        if (now_d < d) {
            age_m--;
            if (age_m < 0) {
                age_y--;
                age_m += 12;
            }
        }
    }
}