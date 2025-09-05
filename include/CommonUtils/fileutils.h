// fileutils.h
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QByteArray>
#include <QFileInfo>
#include <QStringList>

namespace FileUtils {

    QByteArray readFile(const QString &filePath);
    bool replaceOrCreateFile(const QString &filePath, const QByteArray &data);
    bool copyAndOverwrite(const QString &source, const QString &target, QString *errorMessage = nullptr);
    QStringList copyFilesFromDir(const QString &sourcesPath, const QString &targetPath);
    QString searchFile(const QString &baseDir, const QFileInfo &fileSearched, const QStringList &ignoreList = {});
    bool createFolder(const QString &dir);

}

#endif // FILEUTILS_H
