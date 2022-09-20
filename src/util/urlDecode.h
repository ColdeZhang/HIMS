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
     * URL 解码函数
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
}


