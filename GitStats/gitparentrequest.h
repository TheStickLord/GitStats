#ifndef GITPARENTREQUEST_H
#define GITPARENTREQUEST_H

#include "user.h"
#include <QString>
#include <QDir>

class GitParentRequest
{
public:
    GitParentRequest();

    void SetDirectory(QString dir);

    QString GetStatus();

    std::vector<User> GetAuthors();

    QString PullRepo();

private:
    QString workingDir = QDir::currentPath();
};

#endif // GITPARENTREQUEST_H
