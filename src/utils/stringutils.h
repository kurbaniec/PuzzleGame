//
// Created by kurbaniec on 18.12.2021.
//

#ifndef PUZZLE_GAME_STRINGUTILS_H
#define PUZZLE_GAME_STRINGUTILS_H

// See: https://stackoverflow.com/a/874160/12347616
bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

#endif //PUZZLE_GAME_STRINGUTILS_H
