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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

FilaSql *fila_sql_nueva(void)
{
    FilaSql *F = (FilaSql *) malloc(sizeof(FilaSql));
    F->arreglo = NULL;
    F->tamanyo = 0;
    return F;
}

MatrizSql *matriz_sql_nueva(void)
{
    MatrizSql *M = (MatrizSql *) malloc(sizeof(MatrizSql));
    M->arreglo = NULL;
    M->tamanyo = 0;
    return M;
}

void fila_sql_agrega(FilaSql *F, char *palabra)
{
    int i;
    FilaSql *G = fila_sql_nueva();
    G->tamanyo = F->tamanyo;
    G->arreglo = (char **) calloc(G->tamanyo, sizeof(char *));
    for (i = 0; i < G->tamanyo; ++i) {
        G->arreglo[i] = (char *) calloc(strlen(F->arreglo[i]), sizeof(char));
        strcpy(G->arreglo[i], F->arreglo[i]);
    }
    for (i = 0; i < F->tamanyo; ++i) {
        free(F->arreglo[i]);
    }
    free(F->arreglo);
    F->tamanyo = G->tamanyo + 1;
    F->arreglo = (char **) calloc(F->tamanyo, sizeof(char *));
    for (i = 0; i < G->tamanyo; ++i) {
        F->arreglo[i] = (char *) calloc(strlen(G->arreglo[i]), sizeof(char));
        strcpy(F->arreglo[i], G->arreglo[i]);
    }
    for (i = 0; i < G->tamanyo; ++i) {
        free(G->arreglo[i]);
    }
    free(G->arreglo);
    free(G);
    F->arreglo[F->tamanyo - 1] = (char *) calloc(strlen(palabra), sizeof(char));
    strcpy(F->arreglo[F->tamanyo - 1], palabra);
}

void matriz_sql_agrega(MatrizSql *M, FilaSql *F)
{
    int i, j;
    MatrizSql *N = matriz_sql_nueva();
    N->tamanyo = M->tamanyo;
    N->arreglo = (FilaSql **) calloc(N->tamanyo, sizeof(FilaSql *));
    // Copia matriz
    for (i = 0; i < N->tamanyo; ++i) {
        N->arreglo[i] = fila_sql_nueva();
        for (j = 0; j < M->arreglo[i]->tamanyo; ++j) {
            fila_sql_agrega(N->arreglo[i], M->arreglo[i]->arreglo[j]);
        }
    }
    // Libera matriz
    for (i = 0; i < M->tamanyo; ++i) {
        for (j = 0; j < M->arreglo[i]->tamanyo; ++j) {
            free(M->arreglo[i]->arreglo[j]);
        }
        free(M->arreglo[i]->arreglo);
    }
    free(M->arreglo);
    M->tamanyo = N->tamanyo + 1;
    M->arreglo = (FilaSql **) calloc(M->tamanyo, sizeof(FilaSql *));
    // Copia matriz
    for (i = 0; i < N->tamanyo; ++i) {
        M->arreglo[i] = fila_sql_nueva();
        for (j = 0; j < N->arreglo[i]->tamanyo; ++j) {
            fila_sql_agrega(M->arreglo[i], N->arreglo[i]->arreglo[j]);
        }
    }
    // Libera matriz
    for (i = 0; i < N->tamanyo; ++i) {
        for (j = 0; j < N->arreglo[i]->tamanyo; ++j) {
            free(N->arreglo[i]->arreglo[j]);
        }
        free(N->arreglo[i]->arreglo);
    }
    free(N->arreglo);
    free(N);
    M->arreglo[M->tamanyo - 1] = fila_sql_nueva();
    // Agregas fila al final de la matriz
    for (i = 0; i < F->tamanyo; ++i) {
        fila_sql_agrega(M->arreglo[M->tamanyo - 1], F->arreglo[i]);
    }
}

void matriz_sql_muestra(const MatrizSql *M)
{
    int i, j;
    for (i = 0; i < M->tamanyo; ++i) {
        for (j = 0; j < M->arreglo[i]->tamanyo; ++j) {
            printf("%s ", M->arreglo[i]->arreglo[j]);
        }
        printf("\n");
    }
}

void matriz_sql_libera(MatrizSql *M)
{
    int i, j;
    for (i = 0; i < M->tamanyo; ++i) {
        for (j = 0; j < M->arreglo[i]->tamanyo; ++j) {
            free(M->arreglo[i]->arreglo[j]);
        }
        free(M->arreglo[i]);
    }
    free(M->arreglo);
    free(M);
}

DuMySqlConnection *conexion_mysql_nueva(void)
{
    DuMySqlConnection *con =
            (DuMySqlConnection *) malloc(sizeof(DuMySqlConnection));
    con->db = NULL;
    con->pass = NULL;
    con->puerto = -1;
    con->res = NULL;
    con->ser = NULL;
    con->sql = mysql_init(NULL);
    con->usr = NULL;
    con->conectado = false;
    return con;
}

bool conexion_mysql_conecta(DuMySqlConnection *con)
{
    con->conectado = mysql_real_connect(con->sql,
                       con->ser,
                       con->usr,
                       con->pass,
                       con->db,
                       con->puerto,
                       NULL,
                       0) != NULL;
    return con->conectado;
}

void conexion_mysql_desconecta(DuMySqlConnection *con)
{
    mysql_free_result(con->res);
    mysql_close(con->sql);
    con->conectado = false;
}

void conexion_mysql_libera(DuMySqlConnection *con)
{
    free(con);
}

void conexion_mysql_muestra(const DuMySqlConnection *con)
{
    printf("Usuario: %s\n", con->usr);
    printf("Base de datos: %s\n", con->db);
    printf("Contrasenya: %s\n", con->pass);
    printf("Servidor: %s\n", con->ser);
    printf("Puerto: %d\n", con->puerto);
    printf("Conectado: %s\n", con->conectado ? "Si" :  "No");
}

const char *conexion_mysql_error(const DuMySqlConnection *con)
{
    return mysql_error(con->sql);
}

int conexion_mysql_codigo_error(const DuMySqlConnection *con)
{
    return mysql_errno(con->sql);
}

MatrizSql *conexion_mysql_consulta(DuMySqlConnection *con,
                                   const char *declaracion)
{
    if (mysql_query(con->sql, declaracion) != 0) {
        return NULL;
    }
    con->res = mysql_use_result(con->sql);
    const int ncols = mysql_num_fields(con->res);
    MatrizSql *M = matriz_sql_nueva();
    FilaSql *F;
    int i;
    char *valor;
    MYSQL_ROW R = mysql_fetch_row(con->res);
    while (R != NULL) {
        F = fila_sql_nueva();
        for (i = 0; i < ncols; ++i) {
            valor = R[i] == NULL ? "NULL" : R[i];
            fila_sql_agrega(F, valor);
        }
        matriz_sql_agrega(M, F);
        R = mysql_fetch_row(con->res);
    }
    return M;
}

bool conexion_mysql_cambia_de_base_datos(DuMySqlConnection *con, const char *db)
{
    con->db = db;
    return mysql_change_user(con->sql, con->usr, con->pass, con->db) == 0;
}

bool conexion_mysql_ejecuta_declaracion(DuMySqlConnection *con,
                                        const char *declaracion)
{
    return mysql_query(con->sql, declaracion) == 0;
}



