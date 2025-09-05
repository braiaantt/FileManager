#include "ziputils.h"
#include <QProcess>
#include <QVariant>

ZipUtils::ZipUtils(QObject *parent) :
    QObject(parent)
{

}

void ZipUtils::compressFiles(const QString &sourceDirPath, const QString &outputZipPath)
{
    createProcess(sourceDirPath, outputZipPath, ZipUtils::COMPRESS_OP);
}

void ZipUtils::decompressZipFile(const QString &zipFilePath, const QString &destinationPath)
{
    createProcess(zipFilePath, destinationPath, ZipUtils::DECOMPRESS_OP);
}

void ZipUtils::createProcess(const QString &path, const QString &destinationPath, const QString &operation){

    QProcess *process = new QProcess(this);
    process->setProperty(ZipUtils::OPERATION_PROPERTY, operation);

    connect(process, &QProcess::finished, this, &ZipUtils::onProcessFinished);

    process->start("powershell", {
                                  operation,
                                  "-Path", "\"" + path + "\"",
                                  "-DestinationPath", "\"" + destinationPath + "\""});

}

void ZipUtils::onProcessFinished(int exitCode)
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    QString errorMessage = process->readAllStandardError();

    process->deleteLater();

    if(process->property(ZipUtils::OPERATION_PROPERTY).toString() == ZipUtils::COMPRESS_OP){
        emit compressFinished(exitCode, errorMessage);
    } else {
        emit decompressFinished(exitCode, errorMessage);
    }
}
