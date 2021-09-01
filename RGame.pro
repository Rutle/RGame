TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cc \
    rcharactercreation.cc \
    rgame.cc \
    rgamemenu.cc \
    rnameinputpage.cc \
    rclassinputpage.cc \
    rstatinputpage.cc \
    logsystem.cc \
    rraceinputpage.cc \
    components/pagecomponent.cc \
    gameworld/gameobject.cc \
    gameworld/engine.cc \
    gameworld/playerbehaviour.cc \
    gameworld/rmap.cc \
    gameworld/tree.cc \
    gameworld/dungeonmap.cc \
    gameworld/dungeonroom.cc \
    dataloader.cc \
    gameworld/rworldgenerator.cc \
    gameworld/rdungeonfactory.cc \
    gameworld/rgameobjectfactory.cc \
    gameworld/rdata.cc \
    gameworld/monsterbehaviour.cc

win32: LIBS += -L$$PWD/lib/ -lBearLibTerminal

INCLUDEPATH += $$PWD/include \
    $$PWD/components \
    $$PWD/gameworld

DEPENDPATH += $$PWD/include

HEADERS += \
    rcharactercreation.hh \
    rgame.hh \
    rgamemenu.hh \
    rnameinputpage.hh \
    rclassinputpage.hh \
    rstatinputpage.hh \
    logsystem.hh \
    rraceinputpage.hh \
    components/menucomponent.hh \
    components/pagecomponent.hh \
    gameworld/gameobject.hh \
    gameworld/engine.hh \
    components/behaviourcomponent.hh \
    gameworld/playerbehaviour.hh \
    gameworld/rmap.hh \
    gameworld/tree.hh \
    gameworld/dungeonmap.hh \
    gameworld/dungeonroom.hh \
    components/attackablecomponent.hh \
    components/bodycomponent.hh \
    components/destroyablecomponent.hh \
    components/pickupcomponent.hh \
    components/containercomponent.hh \
    dataloader.hh \
    gameworld/rworldgenerator.hh \
    gameworld/rdungeonfactory.hh \
    gameworld/rgameobjectfactory.hh \
    gameworld/rdata.hh \
    gameworld/monsterbehaviour.hh
