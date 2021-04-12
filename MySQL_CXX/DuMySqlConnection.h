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

#ifndef CONEXIONMYSQL_H
#define CONEXIONMYSQL_H

#include "DuSqlServer.h"
#include "DuSqlUser.h"
#include <winsock2.h>
#include <winsock.h>
#include <mysql.h>
#include <vector>

using Matriz = std::vector<std::vector<std::string>>;

std::ostream &operator<<(std::ostream &o, const std::vector<std::string> &v);
std::ostream &operator<<(std::ostream &o, const Matriz &M);

class DuMySqlConnection
{
public:
    DuMySqlConnection()
        : _Sql(mysql_init(nullptr))
        , _Res(nullptr)
    {
        // constructor por defecto
    }

    DuMySqlConnection(const DuSqlServer &Ser, const DuSqlUser &Usr)
        : _Sql(mysql_init(nullptr))
        , _Res(nullptr)
        , _Ser(Ser)
        , _Usr(Usr)
    {
        // constructor normal
    }

    DuMySqlConnection(const DuMySqlConnection &Con)
        : _Sql(Con._Sql)
        , _Res(Con._Res)
        , _Ser(Con._Ser)
        , _Usr(Con._Usr)
    {
        // constructor de copia
    }

    ~DuMySqlConnection()
    {
        // destructor
        desconecta();
    }

    void setServidorSql(const DuSqlServer &Ser)
    {
        _Ser = Ser;
    }

    void setUsuarioSql(const DuSqlUser &Usr)
    {
        _Usr = Usr;
    }

    DuSqlServer getServidorSql() const
    {
        return _Ser;
    }

    DuSqlUser getUsuarioSql() const
    {
        return _Usr;
    }

    MYSQL *getSql() const
    {
        return _Sql;
    }

    MYSQL_RES *getSqlRes() const
    {
        return _Res;
    }

    bool conecta()
    {
        // Conecta con el servidor MySQL
        return mysql_real_connect(_Sql,
                               _Ser.getNombre().c_str(),
                               _Usr.getNombre().c_str(),
                               _Usr.getContrasenya().c_str(),
                               _Usr.getBaseDatos().c_str(),
                               _Ser.getPuerto(),
                               nullptr,
                               0) != nullptr;
    }

    void desconecta()
    {
        // desconecta del servidor MySQL
        mysql_free_result(_Res);
        mysql_close(_Sql);
    }

    std::string error() const
    {
        // El último error obtenido
        return mysql_error(_Sql);
    }

    int codigoError() const
    {
        // El código del último error obtenido
        return mysql_errno(_Sql);
    }

    Matriz consulta(const std::string &declaracion);

    bool ejecutaDeclaracion(const std::string &declaracion)
    {
        return mysql_query(_Sql, declaracion.c_str()) == 0;
    }
private:
    MYSQL *_Sql;
    MYSQL_RES *_Res;
    DuSqlServer _Ser;
    DuSqlUser _Usr;
};

#endif // CONEXIONMYSQL_H
