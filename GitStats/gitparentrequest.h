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

    std::vector<User> GetAuthorsFile(QString file);

    std::vector<User> GetDiffByUser();

    std::vector<User> GetDiffByUserFile(QString file);

    QString PullRepo();

    QStringList GetFiles();

    std::vector<User> GetBlameForFile();

    QString GetRepoName();

private:
    QString workingDir = QDir::currentPath();
};

#endif // GITPARENTREQUEST_H
