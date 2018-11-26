QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    src/parser/SpinParser.cpp \
    src/scanner/SpinScanner.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    hpp/statements/IStatement.h \
    hpp/parser/ISpinAst.h \
    hpp/parser/SpinParser.h \
    hpp/modules/IModule.h \
    hpp/scanner/SpinScanner.h \
    hpp/scanner/SpinTerminals.h \
    hpp/scanner/SpinConstants.h \
    hpp/scanner/SpinLookAheadScanner.h \
    hpp/modules/Proctype.h \
    hpp/SpinAst.h \
    hpp/modules/Module.h \
    hpp/statements/Statement.h \
    hpp/statements/Sequence.h \
    hpp/steps/VariableDeclaration.h \
    hpp/expressions/IExpression.h \
    hpp/statements/StatementExpression.h \
    hpp/modules/GlobalVariableDeclation.h \
    hpp/expressions/IBinaryExpression.h \
    hpp/expressions/BinaryExpression.h \
    hpp/expressions/Expression.h \
    hpp/expressions/ConstantExpression.h \
    hpp/expressions/SymbolExpression.h \
    hpp/ILhs.h \
    hpp/IRhs.h \
    hpp/expressions/UnaryExpression.h \
    hpp/expressions/IdentifierExpression.h \
    hpp/expressions/ConditionalExpression.h \
    hpp/expressions/LabelExpression.h \
    hpp/expressions/RunExpression.h \
    hpp/Priority.h \
    hpp/statements/IfStatement.h \
    hpp/statements/DoStatement.h

