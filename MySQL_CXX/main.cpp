/*
    Copyright (C) 2021  Carlos Enrique Duarte Ortiz (carlosduarte.1@hotmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "DuMySqlConnection.h"

using namespace std;

int main()
{
    DuMySqlConnection mysql;
    DuSqlUser usr;
    DuSqlServer ser;
    usr.setNombre("root");
    usr.setContrasenya("");
    usr.setBaseDatos("");
    ser.setNombre("localhost");
    ser.setPuerto(3306);
    mysql.setUsuarioSql(usr);
    mysql.setServidorSql(ser);
    if (!mysql.conecta()) {
        cerr << mysql.error() << endl;
        return mysql.codigoError();
    }
    cout << "Conectado..." << endl;
    mysql.ejecutaDeclaracion("CREATE DATABASE minuevabase");
    cout << mysql.consulta("SHOW DATABASES") << endl;
    return 0;
}

