#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int pin_pong_cycle = 6;

void reduce(){
    
}

int main(int argc, char** argv) 
{
    int size;
    int rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //rank of process
    MPI_Comm_size(MPI_COMM_WORLD, &size); //how many proccess in execution

    if (size != 2) 
    {
        cout<<"Must be only two process in execution, exits --> ";
        cout<<argv[0];
        return 0;
    }

    int s_rank = (rank + 1) % 2;
    int counter = 0;
    while (counter < pin_pong_cycle) 
    {
        cout<<"rank: "<<rank<<endl;
        if( counter % 2 == rank ) 
        {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, s_rank, 0, MPI_COMM_WORLD);
            cout<<rank<<" sent counter "<<counter<<" to process "<<s_rank<<endl;
        } else 
        {
            MPI_Recv(&counter, 1, MPI_INT, s_rank, 0, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
            cout<<rank<<" received counter "<<counter<<" from process "<<s_rank<<endl;      
        }
    }

      // Initialize the MPI environment. The two arguments to MPI Init are not
      // currently used by MPI implementations, but are there in case future
      // implementations might need the arguments.
      MPI_Init(NULL, NULL);

      // Get the number of processes
      int world_size;
      MPI_Comm_size(MPI_COMM_WORLD, &world_size);

      // Get the rank of the process
      int world_rank;
      MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

      // Get the name of the processor
      char processor_name[MPI_MAX_PROCESSOR_NAME];
      int name_len;
      MPI_Get_processor_name(processor_name, &name_len);

      // Print off a hello world message
      printf("Hello world from processor %s, rank %d out of %d processors\n",
         processor_name, world_rank, world_size);

    MPI_Finalize();


}