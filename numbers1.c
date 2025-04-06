/*
Name:           Tareq Abu El Komboz
StudentID:      A1976365
Description:    This is Assignement 1 Milestone Program. The objective is to find numbers out of order in a ring topology, and print information about them.
*/

// How neighbour relationships between tasks are implemented

// Import libraries
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Initialize variables for each process
    int rank, size;     // Rank of the process and total number of processes
    int number;         // The number held by this process
    int left_number;    // Number received from the left neighbour

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Assign a number to each process based on its rank.
    // Example assignment: Process 0: 5, Process 1: 7, Process 2: 9, Process 3: 1, Process 4: 13
    switch (rank) {
        case 0: 
            number = 5; 
            break;
        case 1: 
            number = 7; 
            break;
        case 2: 
            number = 9; 
            break;
        case 3: 
            number = 1; 
            break;
        case 4: 
            number = 13; 
            break;
        default: 
            number = 0; 
            break;
    }

    // Todo:
    // Master Process
    // Slave Process
    // Calculation of left neigbor rank
    // Calculation of right neigbor rank
    // Left check if in order
    // Right check if in order
    // If one check failed
    //      Print out-of-order warning

    // Indicate that the process has finished executing.
    printf("Process %d has now finished.\n", rank);

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}