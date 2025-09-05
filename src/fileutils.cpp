#include "fileutils.h"
#include <QDir>
#include <QProcess>
#include <QJsonParseError>

QByteArray FileUtils::readFile(const QString &filePath)
{
    QByteArray fileData;
    QFile file(filePath);

    if(file.open(QIODevice::ReadOnly)){
        fileData = file.readAll();
        file.close();
    }

    return fileData;
}

bool FileUtils::replaceOrCreateFile(const QString &filePath, const QByteArray &data)
{
    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        return false;
    }

    file.write(data);
    file.close();
    return true;
}

bool FileUtils::copyAndOverwrite(const QString &source, const QString &target, QString *errorMessage)
{
    QFile targetFile(target);
    if (targetFile.exists() && !targetFile.remove()) {
        if (errorMessage) *errorMessage = "No se pudo eliminar el archivo existente: " + target;
        return false;
    }

    if (!QFile::copy(source, target)) {
        if (errorMessage) *errorMessage = "No se pudo copiar el archivo desde: " + source;
        return false;
    }

    return true;

}

QStringList FileUtils::copyFilesFromDir(const QString &sourcesPath, const QString &targetPath){

    QStringList errors;
    QDir sourcesDir(sourcesPath);
    sourcesDir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

    QFileInfoList entries = sourcesDir.entryInfoList();
    QString folderToIgnore = sourcesDir.dirName();

    for(const QFileInfo &entry : entries){

        QString foundPath = searchFile(targetPath, entry, {folderToIgnore});
        QString errorCopy;

        if(!foundPath.isEmpty()){
            copyAndOverwrite(entry.absoluteFilePath(), foundPath, &errorCopy);
        } else {
            copyAndOverwrite(entry.absoluteFilePath(), QDir(targetPath).filePath(entry.fileName()), &errorCopy);
        }

        if(!errorCopy.isEmpty()) errors.append(errorCopy);

    }

    return errors;

}

QString FileUtils::searchFile(const QString &baseDir, const QFileInfo &fileSearched, const QStringList &ignoreList){

    QDir dir(baseDir);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    QFileInfoList entries = dir.entryInfoList();

    for(const QFileInfo &entry : entries){

        if(!ignoreList.contains(entry.fileName())){

            if(entry.isDir()){

                QString newDir = dir.filePath(entry.fileName());
                QString foundPath = searchFile(newDir, fileSearched, ignoreList);
                if(!foundPath.isEmpty()) return foundPath;

            } else if (entry.isFile()){

                if(entry.fileName() == fileSearched.fileName()){
                    return entry.absoluteFilePath();
                }

            }

        }

    }

    return QString();

}

bool FileUtils::createFolder(const QString &dir){

    QDir folder;

    if(!folder.exists(dir)){
        if(!folder.mkpath(dir)){
            qWarning()<<"Error al crear la carpeta en: "<<dir;
            return false;
        }
    }

    return true;

}

