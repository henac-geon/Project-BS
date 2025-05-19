#pragma once

#ifndef ASCII_ART_REPOSITORY_H
#define ASCII_ART_REPOSITORY_H

#include <string>

namespace AsciiArt {

    int GetConsoleWidth();
    std::string getLine(char ch = '=', int width = -1);

	std::string getWelcomeArt();
	std::string generate_book_art();
	std::string getLevelUpArt();
	std::string getGameOverArt();

    std::string showMaleNPCArt();
    std::string showFemaleNPCArt();
    std::string showClosingArt();
    std::string showRestoreBookArt();
}

#endif // ASCII_ART_REPOSITORY_H
