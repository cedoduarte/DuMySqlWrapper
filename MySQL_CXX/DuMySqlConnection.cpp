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

#include "DuMySqlConnection.h"

using namespace std;

std::ostream &operator<<(std::ostream &o, const std::vector<std::string> &v)
{
    const vector<string>::const_iterator end = v.end();
    vector<string>::const_iterator i = v.begin();
    for (; i != end; ++i) {
        o << *i << ' ';
    }
    return o;
}

std::ostream &operator<<(std::ostream &o, const Matriz &M)
{
    const Matriz::const_iterator end = M.end();
    Matriz::const_iterator i = M.begin();
    for (; i != end; ++i) {
        o << *i << endl;
    }
    return o;
}

Matriz DuMySqlConnection::consulta(const string &declaracion)
{
    if (mysql_query(_Sql, declaracion.c_str()) != 0) {
        return Matriz();
    }
    int i;
    _Res = mysql_use_result(_Sql);
    const int ncols = mysql_num_fields(_Res);
    vector<string> Rfila;
    Matriz MR; // Matriz de resultado
    MYSQL_ROW fila = mysql_fetch_row(_Res);
    while (fila != NULL) {
        for (i = 0; i < ncols; ++i) {
            Rfila.push_back(fila[i] == NULL ? "NULL" : fila[i]);
        }
        MR.push_back(Rfila);
        Rfila.clear();
        fila = mysql_fetch_row(_Res);
    }
    return MR;
}
