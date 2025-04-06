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

    // Determine the neighbours in the ring:
    // Left neighbour: (rank - 1 + size) % size (wrap-around using modulo)
    // Right neighbour: (rank + 1) % size (wrap-around)
    int left = (rank - 1 + size) % size; // Calculation of left neigbor rank
    int right = (rank + 1) % size; // Calculation of right neigbor rank

    /* 
     * Each process sends its own number to its right neighbour and simultaneously receives a number from its left neighbour using MPI_Sendrecv.
     * This ensures that processes communicate only with their immediate neighbours.
     */
    MPI_Sendrecv(
        &number, // msg_buf_p
        1, // msg_size
        MPI_INT, // msg_type
        right, // dest
        0, // tag
        &left_number, // msg_buf_p
        1,  // buf_size
        MPI_INT,  // buf_type
        left,  // source
        0, // tag
        MPI_COMM_WORLD, // communicator
        MPI_STATUS_IGNORE // status_p
    );

    /*
     * For all processes except process 0, check if the number is out of order.
     * A process is out of order if its number is less than the number it received
     * from its left neighbour.
     */
    if (rank != 0) { // All but rank 0 check number to their left, because 0 has no left neighbor
        if (number < left_number) { // Left check if in order, right not needed
            printf("Process %d has at least one number out of order.\n", rank); // If check failed
        }
    }

    // Indicate that the process has finished executing.
    printf("Process %d has now finished.\n", rank);

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}