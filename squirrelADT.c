#include "squirrelADT.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct block
{
    size_t * squirrel;
    size_t cantCols;
}squirrelRow;



typedef struct squirrelCensusCDT
{
    size_t blockSizeMetres;
    squirrelRow * row;
    size_t cantRows;
    size_t count;
    
}squirrelCensusCDT;


/**
* Reserva los recursos para el conteo de ardillas en un parque agrupando las
* cantidades por bloques de tamaño blockSizeMeters metros x blockSizeMeters
* metros desde el extremo superior izquierdo del parque
* Si blockSizeMeters es igual a 0 retorna NULL
*/
squirrelCensusADT newSquirrelCensus(size_t blockSizeMeters)
{
    if(!blockSizeMeters)
        return 0;
    squirrelCensusADT new = calloc(1, sizeof(*new));
    new->blockSizeMetres = blockSizeMeters;
    return new;
}

/**
* Registra una ardilla en el bloque correspondiente al punto (yDistance,
* xDistance) donde
* - yDistance es la distancia vertical en metros del extremo superior 
*   izquierdo del parque
* - xDistance es la distancia horizontal en metros del extremo superior
*   izquierdo del parque
* Retorna cuántas ardillas fueron registradas en ese mismo bloque
*/
size_t countSquirrel(squirrelCensusADT squirrelAdt, size_t yDistance, size_t xDistance)
{
    int col = xDistance / squirrelAdt->blockSizeMetres;
    int row = yDistance / squirrelAdt->blockSizeMetres;
    if(squirrelAdt->cantRows <= row)
    {
        squirrelAdt->row = realloc(squirrelAdt->row,(row+1)* sizeof(*squirrelAdt->row));
        for(int i = squirrelAdt->cantRows; i < row+1 ; i++ )
        {
            squirrelAdt->row[i].cantCols = 0;
            squirrelAdt->row[i].squirrel = NULL;
        }
        squirrelAdt->cantRows = row+1;
    }
    if(squirrelAdt->row[row].cantCols <= col)
    {
        squirrelAdt->row[row].squirrel = realloc(squirrelAdt->row[row].squirrel, (col+1)* sizeof(*squirrelAdt->row[row].squirrel));
        for(int i = squirrelAdt->row[row].cantCols; i <  col+1 ; i++ )
        {
            squirrelAdt->row[row].squirrel[i] = 0;
        }
        squirrelAdt->row[row].cantCols = col+1;
    }
    squirrelAdt->row[row].squirrel[col]++;
    squirrelAdt->count++;
    return squirrelAdt->row[row].squirrel[col];

}

/**
* Retorna cuántas ardillas fueron registradas en el bloque correspondiente
* al punto (yDist, xDist)
*/
size_t squirrelsInBlock(const squirrelCensusADT squirrelAdt, size_t yDist, size_t xDist)
{
    int row = yDist / squirrelAdt->blockSizeMetres;
    int col = xDist / squirrelAdt->blockSizeMetres;
    if(squirrelAdt->cantRows <= row || squirrelAdt->row[row].cantCols < col )
        return 0;
    return squirrelAdt->row[row].squirrel[col];
}


/**
* Libera los recursos utilizados para el conteo de ardillas en un parque
*/
void freeSquirrelCensus(squirrelCensusADT squirrelAdt)
{
    for(int i = 0 ; i <squirrelAdt->cantRows ; i++)
    {
        free(squirrelAdt->row[i].squirrel);
    }
    free(squirrelAdt->row);
    free(squirrelAdt);
}
