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

#ifndef USUARIOSQL_H
#define USUARIOSQL_H

#include <iostream>

class DuSqlUser
{
public:
    DuSqlUser()
        : _nombre("")
        , _contrasenya("")
        , _basedatos("")
    {
        // constructor por defecto
    }

    DuSqlUser(const std::string &nombre,
               const std::string &contrasenya,
               const std::string &basedatos)
        : _nombre(nombre)
        , _contrasenya(contrasenya)
        , _basedatos(basedatos)
    {
        // constructor normal
    }

    DuSqlUser(const DuSqlUser &Usr)
        : _nombre(Usr._nombre)
        , _contrasenya(Usr._contrasenya)
        , _basedatos(Usr._basedatos)
    {
        // constructor de copia
    }

    void setNombre(const std::string &nombre)
    {
        _nombre = nombre;
    }

    void setContrasenya(const std::string &contrasenya)
    {
        _contrasenya = contrasenya;
    }

    void setBaseDatos(const std::string &basedatos)
    {
        _basedatos = basedatos;
    }

    std::string getNombre() const
    {
        return _nombre;
    }

    std::string getContrasenya() const
    {
        return _contrasenya;
    }

    std::string getBaseDatos() const
    {
        return _basedatos;
    }

    inline friend std::ostream &operator<<(std::ostream &o,
                                           const DuSqlUser &Usr);
private:
    std::string _nombre;
    std::string _contrasenya;
    std::string _basedatos;
};

inline std::ostream &operator<<(std::ostream &o, const DuSqlUser &Usr)
{
    return o << '('
             << Usr._nombre
             << ", "
             << Usr._contrasenya
             << ", "
             << Usr._basedatos
             << ')';
}

#endif // USUARIOSQL_H
