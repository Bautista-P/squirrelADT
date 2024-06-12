#include <stdio.h>

typedef struct squirrelCensusCDT * squirrelCensusADT;

/**
* Reserva los recursos para el conteo de ardillas en un parque agrupando las
* cantidades por bloques de tamaño blockSizeMeters metros x blockSizeMeters
* metros desde el extremo superior izquierdo del parque
* Si blockSizeMeters es igual a 0 retorna NULL
*/
squirrelCensusADT newSquirrelCensus(size_t blockSizeMeters);

/**
* Registra una ardilla en el bloque correspondiente al punto (yDistance,
* xDistance) donde
* - yDistance es la distancia vertical en metros del extremo superior 
*   izquierdo del parque
* - xDistance es la distancia horizontal en metros del extremo superior
*   izquierdo del parque
* Retorna cuántas ardillas fueron registradas en ese mismo bloque
*/
size_t countSquirrel(squirrelCensusADT squirrelAdt, size_t yDistance, size_t xDistance);

/**
* Retorna cuántas ardillas fueron registradas en el bloque correspondiente
* al punto (yDist, xDist)
*/
size_t squirrelsInBlock(const squirrelCensusADT squirrelAdt, size_t yDist, size_t xDist);


/**
* Libera los recursos utilizados para el conteo de ardillas en un parque
*/
void freeSquirrelCensus(squirrelCensusADT squirrelAdt);
