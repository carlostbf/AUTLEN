#include "ap.h"

/*struct _transicion {
    char * nombre_simbolo_pila;
    char * nombre_estado_i;
    char * nombre_estado_f;
    char * nombre_simbolo_entrada;
    Palabra* accion;
};*/

struct _AP {
    char* nombre; /*nombre del automata*/
    int num_estados;
    int num_simbolos_entrada;
    int num_simbolos_pila;
    List * sigma; /*lista de palabras para el alfabeto de la entrada*/
    List * gamma; /*lista de palabras para el alfabeto de la pila*/
    List * estados; /*lista de los posibles estados del automata*/
    Estado * estadoInicial; /*estado en el que comienza el automata*/
    Palabra * cadenaEntrada; /*lista de palabras que componen la cadena de entrada*/
    /*ConfiguracionAp * iniConf;*/

    TransicionAP * transiciones;
    ConfiguracionApnd * configuraciones; /*lista de configuraciones actuales del automata*/
    /*Transicion * transicion;*/
    /*quiza algo para transicones lambda*/
};

/**
 * @brief
 */
AP * APNuevo(char * nombre, int num_estados, int num_simbolos_entrada, int num_simbolos_pila) {/*NO TERMINADO*/
    AP * p_ap;
    p_ap = (AP*) malloc(sizeof (AP));
    p_ap->nombre = (char*) calloc(strlen(nombre) + 1, sizeof (char));
    p_ap->num_estados = num_estados;
    p_ap->num_simbolos_entrada = num_simbolos_entrada;
    p_ap->num_simbolos_pila = num_simbolos_pila;

    p_ap->sigma = list_ini((destroy_element_function_type) destroy_p_string,
            (copy_element_function_type) copy_p_string,
            (print_element_function_type) print_p_string,
            (cmp_element_function_type) strcmp);
    p_ap->gamma = list_ini((destroy_element_function_type) destroy_p_string,
            (copy_element_function_type) copy_p_string,
            (print_element_function_type) print_p_string,
            (cmp_element_function_type) strcmp);
    p_ap->estados = list_ini((destroy_element_function_type) estadoElimina,
            (copy_element_function_type) estado_copy,
            (print_element_function_type) estadoImprime,
            (cmp_element_function_type) estadoCompara);

    p_ap->transiciones = transicionAPNueva(nombre, num_simbolos_pila, num_estados, num_simbolos_entrada,
            p_ap->gamma, p_ap->estados, p_ap->sigma);

    return p_ap;
}

/*TODO*/
void APElimina(AP * p_ap) {/*NO TERMINADO*/
    free(p_ap->nombre);
    list_destroy(p_ap->sigma);
    list_destroy(p_ap->gamma);
    list_destroy(p_ap->estados);
    free(p_ap);
}

void APImprime(FILE * fd, AP* p_ap) {
    if (fd == NULL || p_ap == NULL)
        return;
    fprintf(fd, "AP={\t%s\n\n", p_ap->nombre);
    /*TODO rehacer list_print para imprimir en el formato correcto*/
    fprintf(fd, "Sigma=");
    list_print(fd, p_ap->sigma);
    fprintf(fd, "\nGamma=");
    list_print(fd, p_ap->gamma);
    fprintf(fd, "\nQ=");
    list_print(fd, p_ap->estados);
    fprintf(fd, "\n");

    fprintf(fd, "configuracion actual:\n");
    configuracionApImprime(fd, p_ap->iniConf);

    fprintf(fd, "Cadena inicial:\n");
    palabraImprime(fd, p_ap->cadenaEntrada);

    fprintf(fd, "transiciones Lambda Puras:\n");
    relacionImprime(fd, p_ap->transicionesL);


}

/**
 * @brief inserta un simbolo (que es un string) en el alfabeto de la entrada, que es una lista de PALABRAS
 */
AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo) {
    list_insertFirst(p_ap->sigma, simbolo);
    return p_ap;
}

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo) {
    list_insertFirst(p_ap->gamma, simbolo);
    return p_ap;
}

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo) {
    Estado* e;
    e = estadoNuevo(char * nombre, int tipo);
    list_insertInOrder(p_ap->estados, e);
    if (tipo == INICIAL || tipo == INICIAL_Y_FINAL)
        p_ap->estadoInicial = e;
    return p_ap;
}

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f) {
    transicionAPInserta(p_ap->transiciones,
            NULL, nombre_estado_i, nombre_estado_f, NULL,
            NULL);

}

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion) {

    transicionAPInserta(p_ap->transiciones,
            nombre_simbolo_pila, nombre_estado_i, nombre_estado_f, nombre_simbolo_entrada,
            accion);
    return p_ap;
}

/**
 * @brief insertar una letra en la cadena de entrada. La cadena de entrada es una lista de PALABRAS, donde letra (que es un string) es un simbolo de esta cadena de entrada
 */
AP * APInsertaLetra(AP * p_ap, char * letra) {
    palabraInsertaLetra(p_ap->cadenaEntrada, letra);
    return p_ap;
}

/**
 * @brief calcula las relaciones instantaneas. al iniciar el automata, genera transiciones instantaneas que son composicion de otras transiciones instantaneas
 */
AP * APCierraLTransicion(AP * p_ap) {
    if (cierre(p_ap->transiciones))
        return p_ap;
    return NULL;
}

/**
 * genera la configuracion_apnd que contiene el estado inicial y los estados a los que se puede llegar mediante el inicial a traves de transiciones instantaneas
 */
AP * APInicializaEstado(AP * p_ap) {
    Stack * pila;
    Palabra *cadena;
    ConfiguracionAp* p_cap;
    if (p_ap->configuraciones)
        configuracionApndDestroy(p_ap->configuraciones);

    pila = stack_ini((destroy_element_function_type) destroy_p_string,
            (copy_element_function_type) copy_p_string,
            (print_element_function_type) print_p_string,
            (cmp_element_function_type) strcmp);
    p_ap->configuraciones = configuracionApndIni();

    p_cap = configuracionApNueva(p_ap->estadoInicial, pila, p_ap->cadenaEntrada);

    configuracionApndInsert(p_ap->configuraciones, p_cap);
    /*liberar pila y cosas*/
    stack_destroy(pila);
    return p_ap;
}

/**
 * un paso del procesamiento de la entrada: según una transicion posible de hacer y a partir de una configuracion_ap, una entrada y una pila,
 * genera nuevas configuracion_ap consumiendo simbolo de entrada, modificando la pila y cambiando el estado de la nueva con respecto de la antigua
 * (todas las modificaciones se reflejan en la nueva configuracion y no en la configuracion antigua)
 * a partir de una configuracion A, crea una copia B y en esta B realiza las modificaciones que haría el automata si hiciera esa transicion
 */
int APTransita(AP * p_ap) {
    if (p_ap == NULL) return -1;

}

/**
 * recorre la lista de configuraciones_ap (situaciones) y para cada una de ellas, llama a APTransita. si alcanza un estado final con la entrada vacia, termina.
 * Si consume toda la cadena de entrada y no esta en un estado final, termina con error.
 */
int APProcesaEntrada(FILE *fd, AP * p_ap) {

}

void APInicializaCadena(AP * p_ap) {
    palabraElimina(p_ap->cadenaEntrada);
    p_ap->cadenaEntrada = palabraNueva();
}