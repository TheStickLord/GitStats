#include "user.h"

User::User() {}

User::User(int Commits, QString Name, QString Email) {
    this->Commits = Commits;
    this->Name = Name;
    this->Email = Email;
}

User::User(int Commits, int Lines, QString Name, QString Email) {
    this->lines = Lines;
    this->Commits = Commits;
    this->Name = Name;
    this->Email = Email;
}