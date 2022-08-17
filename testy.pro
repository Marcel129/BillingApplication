QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        customer.cpp \
        database.cpp \
        invoice.cpp \
        invoicebase.cpp \
        invoicerecord.cpp \
        invoicetemplate.cpp \
        main.cpp \
        my_classs.cpp \
        products.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    testy_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/car.gif \
    images/mouse.png

HEADERS += \
    config.h \
    customer.h \
    database.h \
    invoice.h \
    invoicebase.h \
    invoicerecord.h \
    invoicetemplate.h \
    my_classs.h \
    products.h
