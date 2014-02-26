CONFIG += debug_and_release qt warn_on
DESTDIR = bin
FORMS = \
    ui/adddialog.ui \
    ui/letter.ui \
    ui/labels.ui \
    ui/measurements.ui \
    ui/universe.ui \
    ui/invoice.ui \
    ui/settings.ui
HEADERS = ../AudioPlugin/src/puretoneaudiometrywidget.h \
 ../AudioPlugin/src/speechaudiometrywidget.h \
    src/view/view_adddialog.h \
    src/view/view_letter.h \
    src/model/model_file.h \
    src/model/model_physician.h \
    src/model/model_letter.h \
    src/model/model_settings.h \
    src/model/model_universe.h \
    src/model/model_invoice.h \
    src/model/model_customer.h \
    src/model/model_entity.h \
    src/model/model_measurements.h \
    src/view/view_universe.h \
    src/view/view_settings.h \
    src/view/view_invoice.h \
    src/view/view_labels.h \
    src/view/view_file.h \
    src/view/view_physician.h \
    src/view/view_insurancecompany.h \
    src/view/view_measurements.h \
    src/presenter/presenter_universe.h \
    src/presenter/presenter_physician.h \
    src/presenter/presenter_file.h \
    src/presenter/presenter_measurements.h \
    src/presenter/presenter_insurancecompany.h \
    src/model/model_insurancecompany.h \
    src/presenter/presenter_invoice.h \
    src/presenter/presenter_labels.h \
    src/presenter/presenter_settings.h \
    src/presenter/presenter_letter.h \
    src/presenter/presenter_letterphysician.h \
    src/presenter/presenter_customer.h \
    src/view/view_customer.h \
    src/presenter/presenter_letterinsurancecompany.h \
    src/presenter/presenter_lettercustomer.h \
    src/model/model_labels.h
MOC_DIR = build
OBJECTS_DIR = build
QT = core gui xml widgets printsupport
RESOURCES += icons.qrc
SOURCES = ../AudioPlugin/src/puretoneaudiometrywidget.cpp \
 ../AudioPlugin/src/speechaudiometrywidget.cpp \
 src/main.cpp \
    src/view/view_adddialog.cpp \
    src/view/view_letter.cpp \
    src/model/model_file.cpp \
    src/model/model_letter.cpp \
    src/model/model_settings.cpp \
    src/presenter/presenter_physician.cpp \
    src/model/model_entity.cpp \
    src/model/model_physician.cpp \
    src/model/model_invoice.cpp \
    src/model/model_customer.cpp \
    src/model/model_measurements.cpp \
    src/model/model_insurancecompany.cpp \
    src/model/model_universe.cpp \
    src/view/view_universe.cpp \
    src/presenter/presenter_file.cpp \
    src/presenter/presenter_measurements.cpp \
    src/presenter/presenter_insurancecompany.cpp \
    src/presenter/presenter_universe.cpp \
    src/view/view_physician.cpp \
    src/view/view_file.cpp \
    src/view/view_labels.cpp \
    src/view/view_invoice.cpp \
    src/view/view_settings.cpp \
    src/view/view_insurancecompany.cpp \
    src/presenter/presenter_invoice.cpp \
    src/view/view_measurements.cpp \
    src/presenter/presenter_labels.cpp \
    src/presenter/presenter_settings.cpp \
    src/presenter/presenter_letter.cpp \
    src/presenter/presenter_letterphysician.cpp \
    src/presenter/presenter_customer.cpp \
    src/view/view_customer.cpp \
    src/presenter/presenter_letterinsurancecompany.cpp \
    src/presenter/presenter_lettercustomer.cpp \
    src/model/model_labels.cpp
TEMPLATE = app
UI_DIR = build
TRANSLATIONS = translations/audioadmin_nl.ts
