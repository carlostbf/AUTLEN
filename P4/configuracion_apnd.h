#ifndef CONFIGURACION_APND_H
#define CONFIGURACION_APND_H

#include "basic_types.h"
#include "configuracion_ap.h"
#include "generic_collections_types.h"
#include "list.h"
typedef struct _ConfiguracionApnd ConfiguracionApnd;
/* Inicializa una configuracion no determinista */
ConfiguracionApnd * configuracionApndIni();
/* Inserta una configuracion determinista en una no determinista. Se realiza una
copia en memoria propia de la coleccion para el nuevo elemento y se asegura que
no haya duplicados*/
ConfiguracionApnd* configuracionApndInsert(ConfiguracionApnd* capnd, const ConfiguracionAp * p_cap);
/* Se obtiene una configuracion determinista de la no determinista, que
desaparece de la coleccion.
No se especifica el orden en el que se extrae */
ConfiguracionAp * configuracionApndExtract(ConfiguracionApnd * capnd);
/* Se devuelve 1 si esta vacia y 0 en caso contrario */
int configuracionApndIsEmpty(const ConfiguracionApnd* capnd);
/* Se devuelve el numero de configuraciones deterministas que hay dentro de la no
determinista */
int configuracionApndSize(const ConfiguracionApnd * capnd);
/* Se imprime todas las configuraciones deterministas. No se especifica en que
orden */
int configuracionApndPrint(FILE *fd, const ConfiguracionApnd* capnd);
/* Se libera toda la memoria asociada con la configuracion no determinista */
void configuracionApndDestroy( ConfiguracionApnd* capnd);

#endif