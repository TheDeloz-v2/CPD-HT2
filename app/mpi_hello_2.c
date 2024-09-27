#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    // Number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if (world_rank == 0) {
        // Process 0 receives messages from all other processes
        printf("Hi, I'm process %d of %d, and I'm receiving!\n", world_rank, world_size);
        for (int i = 1; i < world_size; i++) {
            char message[100];
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", message);
        }
    } else {
        // Other processes send messages to process 0
        char message[100];
        sprintf(message, "Greetings process 0, I'm process %d of %d!", world_rank, world_size);
        printf("Hi, I'm process %d of %d and I'm sending a message to process 0!\n", world_rank, world_size);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
