//
// Created by kurbaniec on 04.06.2021.
// Based on: https://stackoverflow.com/a/22428289/12347616
// And: http://www.cplusplus.com/forum/general/188061/
//

#ifndef BLOCK_GAME_PRINTUTILS_H
#define BLOCK_GAME_PRINTUTILS_H

#include <vector>

template<typename T>
void printer(T t) {
    std::cout << t;
}

template<typename T, typename... Args>
void printer(T t, Args... args) {
    std::cout << t;
    printer(args...);
}

template<typename T>
void print(T t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void print(T t, Args... args) {
    std::cout << t;
    printer(args...);
    std::cout << std::endl;
}

template<typename T>
void print2dVec(std::vector<std::vector<T>> vec) {
    // See: https://stackoverflow.com/a/26937624/12347616
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


#endif //BLOCK_GAME_PRINTUTILS_H
