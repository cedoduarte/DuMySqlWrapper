#    Copyright (C) 2021  Carlos Enrique Duarte Ortiz (carlosduarte.1@hotmail.com)

#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/wamp/bin/mysql/mysql5.6.17/include"
LIBS += -L"C:/wamp/bin/mysql/mysql5.6.17/lib" -lmysql

SOURCES += main.cpp \
    DuMySqlConnection.cpp

HEADERS += \
    DuMySqlConnection.h \
    DuSqlUser.h \
    DuSqlServer.h

QMAKE_CXXFLAGS += -std=gnu++14
