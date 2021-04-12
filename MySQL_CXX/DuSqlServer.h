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

#ifndef SERVIDORSQL_H
#define SERVIDORSQL_H

#include <iostream>

class DuSqlServer
{
public:
    DuSqlServer()
        : _nombre("")
        , _puerto(-1)
    {
        // constructor por defecto
    }

    DuSqlServer(const std::string &nombre,
                int puerto)
        : _nombre(nombre)
        , _puerto(puerto)
    {
        // constructor normal
    }

    DuSqlServer(const DuSqlServer &Ser)
        : _nombre(Ser._nombre)
        , _puerto(Ser._puerto)
    {
        // constructor de copia
    }

    void setNombre(const std::string &nombre)
    {
        _nombre = nombre;
    }

    void setPuerto(int puerto)
    {
        _puerto = puerto;
    }

    std::string getNombre() const
    {
        return _nombre;
    }

    int getPuerto() const
    {
        return _puerto;
    }

    inline friend std::ostream &operator<<(std::ostream &o,
                                           const DuSqlServer &Ser);
private:
    std::string _nombre;
    int _puerto;
};

inline std::ostream &operator<<(std::ostream &o, const DuSqlServer &Ser)
{
    return o << '(' << Ser._nombre << ", " << Ser._puerto << ')';
}

#endif // SERVIDORSQL_H
