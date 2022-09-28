#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

namespace util{
    static unsigned char dec_tab[256] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,  0,  0,  0,  0,
            0, 10, 11, 12, 13, 14, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0, 10, 11, 12, 13, 14, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };

    /**
     * @brief URL 解码函数
     * @param str {const char*} 经URL编码后的字符串
     * @return {char*} 解码后的字符串，返回值不可能为空，需要用 free 释放
     */
    char *acl_url_decode(const char *str){
        int len = (int) strlen(str);
        char *tmp = (char *)malloc(len + 1);

        int i = 0, pos = 0;
        for (i = 0; i < len; i++) {
            if (str[i] != '%')
                tmp[pos] = str[i];
            else if (i + 2 >= len) {  /* check boundary */
                tmp[pos++] = '%';  /* keep it */
                if (++i >= len)
                    break;
                tmp[pos] = str[i];
                break;
            } else if (isalnum(str[i + 1]) && isalnum(str[i + 2])) {
                tmp[pos] = (dec_tab[(unsigned char) str[i + 1]] << 4)
                            + dec_tab[(unsigned char) str[i + 2]];
                i += 2;
            } else
                tmp[pos] = str[i];

            pos++;
        }

        tmp[pos] = '\0';
        return tmp;
    }

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


