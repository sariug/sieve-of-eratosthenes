#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <climits> 
/*
 Sieve of ERATOSTHENES
 8.07.2019
 Uğurcan Sarı
*/
using ULL = long long int;
int main(int argc, char** argv){

	int rank, nproc;
		// Allocate variables	
	ULL global_min=0, local_min=std::numeric_limits<ULL>::max(), iter = 0, sqrt_n;
    ULL local_max, global_max, domain_size, size_of_before_domains, iter_start;
    std::vector<ULL> temp, domain;
	int rem;	div_t divresult;

	// Time 
    double tic; 

	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank );
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    ULL N = atoll(argv[1]);
    if(rank==0)std::cout<<"Number entered is : " << N<<std::endl;
    // Make sure the entered number is larger number of processors being used.
    if(rank == 0 && nproc>=N){
        std::cout<< N << " should be bigger than number of processors( "<<nproc<<")"<<std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
        };
    MPI_Barrier(MPI_COMM_WORLD);


    tic = MPI_Wtime(); 

	// Domain decomposition
	divresult = div(N, nproc);
	rem = divresult.rem;
    if(rank==nproc-1) domain_size = divresult.quot+rem;
    else domain_size = divresult.quot;
    
    std::cout<<"Domain "<<rank<<" has the size of "<<domain_size<<std::endl;
    if(rank==0){ // Getting rid of number 1.
        domain.reserve(domain_size-1);
        domain.resize(domain_size-1);    
    }else{
        domain.reserve(domain_size);
        domain.resize(domain_size);    
    }

    if(rank==nproc-1) size_of_before_domains = divresult.quot*rank;
    else size_of_before_domains = domain_size*rank;
    
    iter_start =  size_of_before_domains+1;
	// Fill the domain 
    for(auto &subdomain:domain)
    {
        if(rank == 0) subdomain = iter_start+iter+1;
        else subdomain = iter_start+iter;
        iter++;
    }
    iter = 0;
    temp.reserve(domain_size);
	
    sqrt_n = sqrt(N);
	// loop
	if(rank==0)std::cout<<"Square Root N : "<<sqrt_n<<std::endl;
	for(;;){
		local_min = domain[0];
		// MPI all reduce
		MPI_Allreduce(&local_min, &global_min, 1, MPI_LONG_LONG_INT, MPI_MIN,MPI_COMM_WORLD);
		if(global_min>= sqrt_n)
			break;
		// Delete the onces we have
        temp.clear();
        
		for(int i = 0; i<domain.size();i++){
			if(domain[i]%global_min )
				temp.push_back(domain[i]);
		}
		domain = temp;
		iter++;
	}
    local_max = *std::max_element(domain.begin(), domain.end());
    MPI_Reduce(&local_max, &global_max, 1, MPI_LONG_LONG, MPI_MAX, 0, MPI_COMM_WORLD );
    
    if (rank ==0)
    {
        std::cout <<"Results: "<< '\n';
        std::cout <<"    Global minimum ="<< global_min <<'\n';
        std::cout<<"    Iteration number = "<<iter<<"\n";
        std::cout <<"    Global maximum ="<< global_max <<'\n';
        printf( "Elapsed time is %f s.\n",  MPI_Wtime() - tic ); 
    }
	
	MPI_Finalize ( );

 	return 0;
}


