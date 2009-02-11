CONFIG += debug_and_release designer qt warn_on
DESTDIR = bin
FORMS = ui/briefarts.ui \
 ui/briefklant.ui \
 ui/briefmutualiteit.ui \
 ui/etiketten.ui \
 ui/factuur.ui \
 ui/instellingen.ui \
 ui/meetgegevens.ui \
 ui/universum.ui
HEADERS = ../AudioPlugin/src/tonaleaudiometriewidget.h \
 ../AudioPlugin/src/vocaleaudiometriewidget.h \
 src/model/model_arts.h \
 src/model/model_briefarts.h \
 src/model/model_briefklant.h \
 src/model/model_briefmutualiteit.h \
 src/model/model_dossier.h \
 src/model/model_entiteit.h \
 src/model/model_factuur.h \
 src/model/model_instellingen.h \
 src/model/model_klant.h \
 src/model/model_meetgegevens.h \
 src/model/model_mutualiteit.h \
 src/model/model_universum.h \
 src/presenter/presenter_arts.h \
 src/presenter/presenter_dossier.h \
 src/presenter/presenter_mutualiteit.h \
 src/presenter/presenter_universum.h \
 src/view/view_arts.h \
 src/view/view_briefarts.h \
 src/view/view_briefklant.h \
 src/view/view_briefmutualiteit.h \
 src/view/view_dossier.h \
 src/view/view_etiketten.h \
 src/view/view_factuur.h \
 src/view/view_instellingen.h \
 src/view/view_meetgegevens.h \
 src/view/view_mutualiteit.h \
 src/view/view_universum.h
MOC_DIR = build
OBJECTS_DIR = build
QT = core gui xml
RESOURCES += icons.qrc
SOURCES = ../AudioPlugin/src/tonaleaudiometriewidget.cpp \
 ../AudioPlugin/src/vocaleaudiometriewidget.cpp \
 src/main.cpp \
 src/model/model_arts.cpp \
 src/model/model_briefarts.cpp \
 src/model/model_briefklant.cpp \
 src/model/model_briefmutualiteit.cpp \
 src/model/model_dossier.cpp \
 src/model/model_entiteit.cpp \
 src/model/model_factuur.cpp \
 src/model/model_instellingen.cpp \
 src/model/model_klant.cpp \
 src/model/model_meetgegevens.cpp \
 src/model/model_mutualiteit.cpp \
 src/model/model_universum.cpp \
 src/presenter/presenter_arts.cpp \
 src/presenter/presenter_dossier.cpp \
 src/presenter/presenter_mutualiteit.cpp \
 src/presenter/presenter_universum.cpp \
 src/view/view_arts.cpp \
 src/view/view_briefarts.cpp \
 src/view/view_briefklant.cpp \
 src/view/view_briefmutualiteit.cpp \
 src/view/view_dossier.cpp \
 src/view/view_etiketten.cpp \
 src/view/view_factuur.cpp \
 src/view/view_instellingen.cpp \
 src/view/view_meetgegevens.cpp \
 src/view/view_mutualiteit.cpp \
 src/view/view_universum.cpp
TEMPLATE = app
UI_DIR = build
