#pragma once
#ifndef SCIENCEBOOK_H
#define SCIENCEBOOK_H

#include "Book.h"
#include <iostream>

class ScienceBook : public Book {
public:
    ScienceBook(const std::string& title, const std::string& description, int length);
    void repair() override;
    void displayInfo() const override;
};

#endif // SCIENCEBOOK_H
