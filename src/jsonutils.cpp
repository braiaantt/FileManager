#include "jsonutils.h"
#include <QJsonParseError>

bool JsonUtils::isValid(const QByteArray &data){

    QJsonParseError parseError;
    QJsonDocument::fromJson(data, &parseError);

    if(parseError.error != QJsonParseError::NoError){
        return false;
    }
    return true;
}
