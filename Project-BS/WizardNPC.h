#pragma once
#ifndef WIZARDNPC_H
#define WIZARDNPC_H

#include "NPC.h"
#include <iostream>

class WizardNPC : public NPC {
public:
    WizardNPC(const std::string& name);
    Book* requestBook(const std::vector<Book*>& candidates) override;
    bool rateBook(Book* book) override;
    void compensateForDamage(Book* book) override;
};

#endif // WIZARDNPC_H
