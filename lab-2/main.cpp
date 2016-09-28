#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int pin_pong_cycle = 6;

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); //rank of process
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size); //how many proccess in execution

  if (size != 2) 
  {
    cout<<"Must be only two process in execution, exits --> ";
    cout<<argv[0];
    return 0;
  }

  int counter = 0;
  int s_rank = (rank + 1) % 2;
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
  MPI_Finalize();
}