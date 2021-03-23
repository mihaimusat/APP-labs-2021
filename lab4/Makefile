CC=mpicc
FLAGS=-O2 -w

all: mpi_hello mpi_bandwidth mpi_mm mpi_pi_send mpi_latency   

clean: 
	/bin/rm -f initial.dat final.dat mpi_bandwidth mpi_mm mpi_pi_send mpi_latency mpi_hello
     
mpi_hello:  mpi_hello.c
	$(CC) $(FLAGS) mpi_hello.c -o mpi_hello

mpi_bandwidth:  mpi_bandwidth.c
	$(CC) $(FLAGS) mpi_bandwidth.c -o mpi_bandwidth

mpi_mm:  mpi_mm.c
	$(CC) $(FLAGS) mpi_mm.c -o mpi_mm

mpi_pi_send:  mpi_pi_send.c
	$(CC) $(FLAGS) mpi_pi_send.c -o mpi_pi_send

mpi_latency:  mpi_latency.c 
	$(CC) $(FLAGS) mpi_latency.c -o mpi_latency
