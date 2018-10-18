TEMPLATE = subdirs

SUBDIRS += \
    QSpinLib \
    QSpin

QSpin.depends = QSpinLib
QSpinTesting.depends = QSpinLib
QProcessSpinTesting.depends = QSpinLib
