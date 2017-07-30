#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    Shape_Triangle,
    Shape_Square,
    Shape_Circle,
} Shape;

typedef enum
{
    Color_Blue,
    Color_Green,
    Color_Red,
    Color_Orange,
    Color_Pink,
    Color_Yellow
} Color;

typedef struct
{
    Shape shape;
    Color color;
} Tile;

int main(int argc, char *argv[])
{
    // NOTE(nox): Using ideas from https://www.math.ksu.edu/math551/math551a.f06/lights_out.pdf

    // NOTE(nox): Puzzle Example
    int numberOfRows = 4;
    int numberOfColumns = 3;
    int numberOfTiles = numberOfRows*numberOfColumns;
    Tile tiles[] = {
        {Shape_Square, Color_Blue}, {Shape_Circle, Color_Pink}, {Shape_Square, Color_Pink},
        {Shape_Square, Color_Yellow}, {Shape_Triangle, Color_Orange}, {Shape_Square, Color_Pink},
        {Shape_Triangle, Color_Red}, {Shape_Triangle, Color_Yellow}, {Shape_Triangle, Color_Red},
        {Shape_Triangle, Color_Green}, {Shape_Square, Color_Green}, {Shape_Circle, Color_Green},
    };

    char *matrixA = calloc(sizeof(*matrixA), numberOfTiles*numberOfTiles);
    for(int unknown = 0;
        unknown < numberOfTiles;
        ++unknown)
    {
        for(int testTile = 0;
            testTile < numberOfTiles;
            ++testTile)
        {
            matrixA[unknown*numberOfTiles + testTile] = (tiles[unknown].shape == tiles[testTile].shape ||
                                                         tiles[unknown].color == tiles[testTile].color);
        }
    }

    char *matrixB = malloc(sizeof(*matrixB)*numberOfTiles*1);
    for(int tile = 0;
        tile < numberOfTiles;
        ++tile)
    {
        matrixB[tile] = 1;
    }

    for(int diagonal = 0;
        diagonal < numberOfTiles;
        ++diagonal)
    {
        for(int i = diagonal;
            i < numberOfTiles;
            ++i)
        {
            if(matrixA[i*numberOfTiles + diagonal])
            {
                if(i != diagonal)
                {
                    for(int j = diagonal;
                        j < numberOfTiles;
                        ++j)
                    {
                        int tmp = matrixA[i*numberOfTiles + j];
                        matrixA[i*numberOfTiles + j] = matrixA[diagonal*numberOfTiles + j];
                        matrixA[diagonal*numberOfTiles + j] = tmp;
                    }
                    int tmp = matrixB[i];
                    matrixB[i] = matrixB[diagonal];
                    matrixB[diagonal] = tmp;
                }
                break;
            }
        }

        for(int i = diagonal+1;
            i < numberOfTiles;
            ++i)
        {
            if(matrixA[i*numberOfTiles + diagonal])
            {
                for(int j = diagonal;
                    j < numberOfTiles;
                    ++j)
                {
                    matrixA[i*numberOfTiles + j] ^= matrixA[diagonal*numberOfTiles + j];
                }
                matrixB[i] ^= matrixB[diagonal];
            }
        }
    }

    for(int diagonal = numberOfTiles - 1;
        diagonal > 0;
        --diagonal)
    {
        if(matrixA[diagonal*numberOfTiles + diagonal])
        {
            for(int i = diagonal - 1;
                i >= 0;
                --i)
            {
                if(matrixA[i*numberOfTiles + diagonal])
                {
                    for(int j = diagonal;
                        j < numberOfTiles;
                        ++j)
                    {
                        matrixA[i*numberOfTiles + j] ^= matrixA[diagonal*numberOfTiles + j];
                    }
                    matrixB[i] ^= matrixB[diagonal];
                }
            }
        }
    }

    puts("Matrix result:");
    for(int i = 0;
        i < numberOfTiles;
        ++i)
    {
        for(int j = 0;
            j < numberOfTiles;
            ++j)
        {
            printf("%d ", matrixA[i*numberOfTiles + j]);
        }
        printf("| %d\n", matrixB[i]);
    }

    puts("\nSolution:");
    for(int i = 0;
        i < numberOfRows;
        ++i)
    {
        printf("|");
        for(int j = 0;
            j < numberOfColumns;
            ++j)
        {
            printf(" %c |", matrixB[i*numberOfColumns + j] ? 'X' : ' ');
        }
        puts("");
    }

    return 0;
}
