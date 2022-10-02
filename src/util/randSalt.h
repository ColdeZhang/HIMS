#pragma once

#include <random>

namespace util{
    /**
     * @name randSalt
     * @brief 随机生成一段长度为64的用于加密的密钥
     * @return 密钥
     */
    char *randSalt(){
        char *salt = new char[64];
        for(int i = 0; i < 64; i++){
            salt[i] = rand() % 26 + 'a';
        }
        return salt;
    }


} // namespace util