#include "user.h"

User::User() {}

User::User(int Commits, QString Name, QString Email) {
    this->Commits = Commits;
    this->Name = Name;
    this->Email = Email;
}