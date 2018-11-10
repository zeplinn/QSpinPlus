#ifndef JSONQSPINPLUSSCHEMEIDS_H
#define JSONQSPINPLUSSCHEMEIDS_H
#include <QColor>
#include <QJsonArray>
#include <QJsonObject>
struct jsonQspinPlusSchemeIds{
    // group members
    static constexpr const char  button[]           = "button";
    static constexpr const char  spinbox[]          = "spinbox";
    static constexpr const char  combobox[]         = "combobox";
    static constexpr const char  general[]          = "general";
    static constexpr const char  promelaEditor[]           = "promelaEditor";
    static constexpr const char  syntaxHighlighter[]= "syntaxHighlighter";

    //value members
    static constexpr const char  foreground[]       = "foreground";
    static constexpr const char  background[]       = "background";
    static constexpr const char  pressed[]          = "pressed";
    static constexpr const char  border[]           = "border";
    static constexpr const char  input[]            = "input";
    static constexpr const char  spinner[]          = "spinner";
    static constexpr const char  icon[]             = "icon";
    static constexpr const char  hovered[]          = "hovered";
    static constexpr const char  menubarGradiant0[] = "menubarGradiant0";
    static constexpr const char  menubarGradiant1[] = "menubarGradiant1";
    static constexpr const char  fontFamily[]       = "fontFamily";
    static constexpr const char  pointSize[]        = "pointSize";
    static constexpr const char  tabIndents[]        = "tabIndents";
    static constexpr const char  selectedText[]        = "selectedText";


    static constexpr const char  classes[]          = "classes";
    static constexpr const char  keywords[]         = "keywords";
    static constexpr const char  comments[]         = "comments";
    static constexpr const char  types[]            = "types";
    static constexpr const char  operators[]        = "operators";
    static constexpr const char  numbers[]          = "numbers";
    static constexpr const char  strings[]          = "strings";
    bool isValidRGBArray( QJsonObject& obj,const char id[]);
    bool isValidInt(QJsonObject& obj,const char id[]);
    bool isValidString(QJsonObject& obj,const char id []);
    QColor toColor(const char id[],const QJsonObject& obj);
};
#endif // JSONQSPINPLUSSCHEMEIDS_H
