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
#include <stdio.h>

int main(void)
{
    DuMySqlConnection *mysql = conexion_mysql_nueva();
    mysql->ser = "localhost";
    mysql->puerto = 3306;
    mysql->usr = "root";
    mysql->pass = "";
    mysql->db = "";
    conexion_mysql_conecta(mysql);
    if (!mysql->conectado) {
        fprintf(stderr, "Error: %s\n", conexion_mysql_error(mysql));
        return conexion_mysql_codigo_error(mysql);
    }
    conexion_mysql_muestra(mysql);
    printf("\n");
    MatrizSql *M;
    conexion_mysql_ejecuta_declaracion(mysql, "CREATE DATABASE mibase");
    M = conexion_mysql_consulta(mysql, "SHOW DATABASES");
    matriz_sql_muestra(M);
    matriz_sql_libera(M);
    conexion_mysql_cambia_de_base_datos(mysql, "mibase");
    conexion_mysql_ejecuta_declaracion(mysql,
                            "CREATE TABLE mitabla (id int, primary key(id))");
    printf("\n");
    M = conexion_mysql_consulta(mysql, "SHOW TABLES");
    matriz_sql_muestra(M);
    matriz_sql_libera(M);
    conexion_mysql_ejecuta_declaracion(mysql, "DROP DATABASE mibase");
    conexion_mysql_desconecta(mysql);
    conexion_mysql_libera(mysql);
    return 0;
}

