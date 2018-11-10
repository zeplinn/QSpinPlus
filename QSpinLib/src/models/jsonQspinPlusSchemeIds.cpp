#include "qspin/models/jsonQspinPlusSchemeIds.h"

bool jsonQspinPlusSchemeIds::isValidRGBArray(QJsonObject &obj, const char id[]){
    QJsonArray j = obj[id].toArray();
    if(j.count()!=3) // r,g,b color channels
    {
        // notify gui
        return false;
    }
    for(auto jvalue : j){
        int colorCode = jvalue.toInt(-1);
        if(colorCode<0 || colorCode >256) // single color channel range [ 0..255 ]
        {
            // notify gui
            return false;
        }
    }
    return true;
}

bool jsonQspinPlusSchemeIds::isValidInt(QJsonObject &obj, const char id[]){
    return obj[id].toInt(-1) >= 0;
}

bool jsonQspinPlusSchemeIds::isValidString(QJsonObject &obj, const char id[]){
    return ! (obj[id].toString("__not__") == "__not__" );
}

QColor jsonQspinPlusSchemeIds::toColor(const char id[], const QJsonObject &obj){
    QJsonArray jrgb = obj[id].toArray();
    if(jrgb.count()<3){
        //notify
        throw QString("invalid rgb array: %1").arg(id);

    }
    // red, green, blue (rgb)
    return  QColor(jrgb[0].toInt(255), jrgb[1].toInt(255), jrgb[2].toInt(255));
}
