TEMPLATE = app

QT += qml quick location network
CONFIG += c++11

SOURCES += src/main.cpp \
    src/testobject.cpp \
    src/pokemon.cpp \
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
    third_party/xxHash/xxhash.cpp \
    src/encounterdata.cpp \
    src/pokemondata.cpp

RESOURCES += resources/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    src/testobject.h \
    src/pokemon.h \
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
    third_party/xxHash/xxhash.h \
    src/encounterdata.h \
    src/pokemondata.h

FORMS +=

unix:!macx: LIBS += -L$$PWD/./libs -lcrypto -lprotobuf -lprotoc -lencrypt -lgflags

unix:!macx: LIBS += -L$$PWD/third_party/s2-geometry-library/geometry/ -ls2cellid -ls2util

INCLUDEPATH += $$PWD/third_party/s2-geometry-library/geometry
DEPENDPATH += $$PWD/third_party/s2-geometry-library/geometry
