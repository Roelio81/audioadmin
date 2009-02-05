CONFIG += console debug_and_release qt warn_on
DESTDIR = bin
FORMS = ui/aboutdialog.ui \
 ui/backupdialog.ui \
 ui/briefartsdialog.ui \
 ui/briefklantdialog.ui \
 ui/briefmutualiteitdialog.ui \
 ui/etikettendialog.ui \
 ui/factuurdialog.ui \
 ui/instellingendialog.ui \
 ui/mainwindow.ui \
 ui/restoredialog.ui
HEADERS = src/artsmodel.h \
 src/artspresenter.h \
 src/artsview.h \
 src/backupdialogimpl.h \
 src/briefarts.h \
 src/briefartsdialogimpl.h \
 src/briefklant.h \
 src/briefmutualiteit.h \
 src/dossiermodel.h \
 src/dossierpresenter.h \
 src/dossierview.h \
 src/etikettendialogimpl.h \
 src/factuur.h \
 src/factuurdialogimpl.h \
 src/instellingendialogimpl.h \
 src/klantmodel.h \
 src/mainwindowimpl.h \
 src/meetgegevens.h \
 src/mutualiteitmodel.h \
 src/mutualiteitpresenter.h \
 src/mutualiteitview.h \
 src/restoredialogimpl.h \
 src/worldmodel.h \
 src/worldpresenter.h \
 src/briefklantdialogimpl.h \
 src/briefmutualiteitdialogimpl.h
MOC_DIR = build
OBJECTS_DIR = build
QT = core gui xml
RESOURCES += icons.qrc
SOURCES = src/artsmodel.cpp \
 src/artspresenter.cpp \
 src/artsview.cpp \
 src/backupdialogimpl.cpp \
 src/briefarts.cpp \
 src/briefartsdialogimpl.cpp \
 src/briefklant.cpp \
 src/briefmutualiteit.cpp \
 src/dossiermodel.cpp \
 src/dossierpresenter.cpp \
 src/dossierview.cpp \
 src/etikettendialogimpl.cpp \
 src/factuur.cpp \
 src/factuurdialogimpl.cpp \
 src/instellingendialogimpl.cpp \
 src/klantmodel.cpp \
 src/main.cpp \
 src/mainwindowimpl.cpp \
 src/meetgegevens.cpp \
 src/mutualiteitmodel.cpp \
 src/mutualiteitpresenter.cpp \
 src/mutualiteitview.cpp \
 src/restoredialogimpl.cpp \
 src/worldmodel.cpp \
 src/worldpresenter.cpp \
 src/briefklantdialogimpl.cpp \
 src/briefmutualiteitdialogimpl.cpp
TEMPLATE = app
UI_DIR = build
