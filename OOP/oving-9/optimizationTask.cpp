#include "Stopwatch.h"
#include <vector>
#include <iostream>

// Utdelt program til oppgave 3

// BEGIN 3b
// Optimalisering: tar inn matrix som const referanse for aa unngaa kopiering
double sumMatrix(const std::vector<std::vector<double>>& matrix){
    double sum = 0;
    for (size_t row = 0; row < matrix.size(); row++){
        for (size_t col = 0; col < matrix[row].size(); col++){
            // Bruker [] istedenfor .at() for aa unngaa bounds-checking overhead
            sum += matrix[row][col];
        }
    }
    return sum;
}

// Optimalisering: fjerner unodvendig dobbel-lokke, setter kun diagonale elementer
void setDiagonalValue(std::vector<std::vector<double>>& matrix, double newValue){
    for (size_t i = 0; i < matrix.size(); i++){
        // Trenger bare sette diagonal-elementene, ikke iterere gjennom hele matrisen
        matrix[i][i] = newValue;
    }
}

void optimizationTask(){
    Stopwatch stopwatch;
    stopwatch.start();
    const int matrixSize = 10000;

    // Oppretter nullmatrisen direkte ved bruk av konstruktoren som tar inn antall og verdi.
    std::vector<std::vector<double>> matrix(matrixSize, std::vector<double>(matrixSize, 0.0));

    // Setter alle elementer paa diagonalen til 0.41
    setDiagonalValue(matrix, 0.41);

    // Summerer alle elementene i matrisen
    double total = sumMatrix(matrix);

    double coolerNumber = total + 2;
    std::cout << "TDT" << coolerNumber << std::endl;

    std::cout << "Time taken: " << stopwatch.stop() << "seconds" << std::endl;
}
// END 3b
