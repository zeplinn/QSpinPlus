TEMPLATE = subdirs

SUBDIRS += \
    QSpinLib \
    QSpin #\
    #SpinParser

QSpin.depends = QSpinLib
QSpinTesting.depends = QSpinLib
QProcessSpinTesting.depends = QSpinLib
