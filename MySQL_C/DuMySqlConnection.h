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

#include <stdbool.h>
#include <winsock2.h>
#include <winsock.h>
#include <mysql.h>

typedef struct FilaSql FilaSql;
typedef struct MatrizSql MatrizSql;
typedef struct DuMySqlConnection DuMySqlConnection;

struct FilaSql
{
    char **arreglo;
    int tamanyo;
};

struct MatrizSql
{
    FilaSql **arreglo;
    int tamanyo;
};

struct DuMySqlConnection
{
    MYSQL *sql;
    MYSQL_RES *res;
    bool conectado;
    const char *usr;
    const char *pass;
    const char *db;
    const char *ser;
    int puerto;
};

// FilaSql funciones
FilaSql *fila_sql_nueva(void);

void fila_sql_agrega(FilaSql *F, char *palabra);

// MatrizSql funciones
MatrizSql *matriz_sql_nueva(void);

void matriz_sql_agrega(MatrizSql *M, FilaSql *F);

void matriz_sql_muestra(const MatrizSql *M);

void matriz_sql_libera(MatrizSql *M);

// ConexionMySql funciones
DuMySqlConnection *conexion_mysql_nueva(void);

bool conexion_mysql_conecta(DuMySqlConnection *con);

void conexion_mysql_desconecta(DuMySqlConnection *con);

void conexion_mysql_libera(DuMySqlConnection *con);

void conexion_mysql_muestra(const DuMySqlConnection *con);

const char *conexion_mysql_error(const DuMySqlConnection *con);

int conexion_mysql_codigo_error(const DuMySqlConnection *con);

MatrizSql *conexion_mysql_consulta(DuMySqlConnection *con,
                                   const char *declaracion);

bool conexion_mysql_cambia_de_base_datos(DuMySqlConnection *con,
                                         const char *db);

bool conexion_mysql_ejecuta_declaracion(DuMySqlConnection *con,
                                        const char *declaracion);

#endif // CONEXIONMYSQL_H
