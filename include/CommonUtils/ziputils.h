#ifndef ZIPUTILS_H
#define ZIPUTILS_H

#include <QObject>
#include <QString>

class ZipUtils : public QObject
{
    Q_OBJECT

public:
    explicit ZipUtils(QObject *parent = nullptr);
    void compressFiles(const QString &sourceDirPath, const QString &outputZipPath);
    void decompressZipFile(const QString &zipFilePath, const QString &destinationPath);

public slots:
    void onProcessFinished(int exitCode);

signals:
    void compressFinished(int exitCode, const QString &error);
    void decompressFinished(int exitCode, const QString &error);

private:
    static constexpr const char *OPERATION_PROPERTY = "operation";
    static inline const QString COMPRESS_OP = "Compress-Archive";
    static inline const QString DECOMPRESS_OP = "Expand-archive";

    void createProcess(const QString &path, const QString &destinationPath, const QString &operation);

};

#endif // ZIPUTILS_H
