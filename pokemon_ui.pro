TEMPLATE = app

QT += qml quick location network gui widgets
CONFIG += c++11

SOURCES += src/main.cpp \
    src/testobject.cpp \
    src/pokemon.cpp \
    src/logindialog.cpp \
    src/mainwindow.cpp \
    src/authptc.cpp \
    src/authgoogle.cpp \
    src/pgoclient.cpp \
    src/proto/POGOProtos.Data.Battle.pb.cc \
    src/proto/POGOProtos.Data.Capture.pb.cc \
    src/proto/POGOProtos.Data.Gym.pb.cc \
    src/proto/POGOProtos.Data.Logs.pb.cc \
    src/proto/POGOProtos.Data.pb.cc \
    src/proto/POGOProtos.Data.Player.pb.cc \
    src/proto/POGOProtos.Enums.pb.cc \
    src/proto/POGOProtos.Inventory.Item.pb.cc \
    src/proto/POGOProtos.Inventory.pb.cc \
    src/proto/POGOProtos.Map.Fort.pb.cc \
    src/proto/POGOProtos.Map.pb.cc \
    src/proto/POGOProtos.Map.Pokemon.pb.cc \
    src/proto/POGOProtos.Networking.Envelopes.pb.cc \
    src/proto/POGOProtos.Networking.Requests.Messages.pb.cc \
    src/proto/POGOProtos.Networking.Requests.pb.cc \
    src/proto/POGOProtos.Networking.Responses.pb.cc \
    src/proto/POGOProtos.Settings.Master.Item.pb.cc \
    src/proto/POGOProtos.Settings.Master.pb.cc \
    src/proto/POGOProtos.Settings.Master.Pokemon.pb.cc \
    src/proto/POGOProtos.Settings.pb.cc \
    src/authfactory.cpp \
    third_party/xxHash/xxhash.cpp

RESOURCES += resources/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    src/testobject.h \
    src/pokemon.h \
    src/logindialog.h \
    src/mainwindow.h \
    src/authptc.h \
    src/authgoogle.h \
    src/pgoclient.h \
    src/proto/POGOProtos.Data.Battle.pb.h \
    src/proto/POGOProtos.Data.Capture.pb.h \
    src/proto/POGOProtos.Data.Gym.pb.h \
    src/proto/POGOProtos.Data.Logs.pb.h \
    src/proto/POGOProtos.Data.pb.h \
    src/proto/POGOProtos.Data.Player.pb.h \
    src/proto/POGOProtos.Enums.pb.h \
    src/proto/POGOProtos.Inventory.Item.pb.h \
    src/proto/POGOProtos.Inventory.pb.h \
    src/proto/POGOProtos.Map.Fort.pb.h \
    src/proto/POGOProtos.Map.pb.h \
    src/proto/POGOProtos.Map.Pokemon.pb.h \
    src/proto/POGOProtos.Networking.Envelopes.pb.h \
    src/proto/POGOProtos.Networking.Requests.Messages.pb.h \
    src/proto/POGOProtos.Networking.Requests.pb.h \
    src/proto/POGOProtos.Networking.Responses.pb.h \
    src/proto/POGOProtos.Settings.Master.Item.pb.h \
    src/proto/POGOProtos.Settings.Master.pb.h \
    src/proto/POGOProtos.Settings.Master.Pokemon.pb.h \
    src/proto/POGOProtos.Settings.pb.h \
    src/iauth.h \
    src/authfactory.h \
    third_party/xxHash/xxhash.h

FORMS += \
    ui/logindialog.ui \
    ui/mainwindow.ui

unix:!macx: LIBS += -L$$PWD/./libs -lcrypto -lprotobuf -lprotoc -lencrypt -lgflags

unix:!macx: LIBS += -L$$PWD/third_party/s2-geometry-library/geometry/ -ls2cellid -lgoogle-strings -lgoogle-base -lgoogle-util-math -lgoogle-util-hash

INCLUDEPATH += $$PWD/third_party/s2-geometry-library/geometry
DEPENDPATH += $$PWD/third_party/s2-geometry-library/geometry

unix:!macx: PRE_TARGETDEPS += $$PWD/third_party/s2-geometry-library/geometry/libs2cellid.a
