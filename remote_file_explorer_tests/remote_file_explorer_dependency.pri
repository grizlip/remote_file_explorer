SOURCES += \
    ../remote_file_explorer_server/processrequest.cpp
HEADERS += \
    ../remote_file_explorer_server/processrequest.h

INCLUDEPATH += ../remote_file_explorer_server/

SOURCES += \
    ../remote_file_explorer_library/request.cpp \
    ../remote_file_explorer_library/response.cpp
HEADERS +=\
    ../remote_file_explorer_library/request.h \
    ../remote_file_explorer_library/response.h \

INCLUDEPATH += ../remote_file_explorer_library/

SOURCES += \
    ../remote_file_explorer_client/serveraccess.cpp \
    ../remote_file_explorer_client/servercommunication.cpp

HEADERS += \
    ../remote_file_explorer_client/serveraccess.h \
    ../remote_file_explorer_client/servercommunication.h

INCLUDEPATH += ../remote_file_explorer_client/


