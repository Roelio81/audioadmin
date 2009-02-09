CONFIG += qt warn_on designer release
DESTDIR = bin
FORMS = ui/briefartsdialog.ui \
 ui/briefklantdialog.ui \
 ui/briefmutualiteitdialog.ui \
 ui/etikettendialog.ui \
 ui/factuurdialog.ui \
 ui/instellingendialog.ui \
 ui/mainwindow.ui \
 ui/meetgegevensdialog.ui
HEADERS = src/model/arts.h \
 src/model/briefarts.h \
 src/model/briefklant.h \
 src/model/briefmutualiteit.h \
 src/model/dossier.h \
 src/model/factuur.h \
 src/model/klant.h \
 src/model/meetgegevens.h \
 src/model/mutualiteit.h \
 src/model/universum.h \
 src/presenter/universum.h \
 src/presenter/arts.h \
 src/presenter/dossier.h \
 src/presenter/mutualiteit.h \
 src/view/universum.h \
 src/view/arts.h \
 src/view/briefarts.h \
 src/view/briefklant.h \
 src/view/briefmutualiteit.h \
 src/view/dossier.h \
 src/view/etiketten.h \
 src/view/factuur.h \
 src/view/instellingen.h \
 src/view/meetgegevens.h \
 src/view/mutualiteit.h
MOC_DIR = build
OBJECTS_DIR = build
QT = core gui xml
RESOURCES += icons.qrc
SOURCES = src/model/arts.cpp \
 src/model/briefarts.cpp \
 src/model/briefklant.cpp \
 src/model/briefmutualiteit.cpp \
 src/model/dossier.cpp \
 src/model/factuur.cpp \
 src/model/klant.cpp \
 src/model/meetgegevens.cpp \
 src/model/mutualiteit.cpp \
 src/model/universum.cpp \
 src/presenter/arts.cpp \
 src/presenter/dossier.cpp \
 src/presenter/mutualiteit.cpp \
 src/presenter/universum.cpp \
 src/view/arts.cpp \
 src/view/briefarts.cpp \
 src/view/briefklant.cpp \
 src/view/briefmutualiteit.cpp \
 src/view/dossier.cpp \
 src/view/etiketten.cpp \
 src/view/factuur.cpp \
 src/view/instellingen.cpp \
 src/view/meetgegevens.cpp \
 src/view/mutualiteit.cpp \
 src/view/universum.cpp
TEMPLATE = app
UI_DIR = build
