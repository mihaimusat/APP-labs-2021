#!/bin/bash

module load libraries/openmpi-2.0.1-gcc-5.4.0
module load mpi/openmpi-x86_64

echo "Rulare Bandwidth Timing Test"
mpirun --mca btl_tcp_if_include eth0 -np 4 ./mpi_bandwidth

echo "Rulare Round Trip Latency Timing Test"
mpirun --mca btl_tcp_if_include eth0 -np 4 ./mpi_latency

echo "Rulare Matrix Multiply"
mpirun --mca btl_tcp_if_include eth0 -np 4 ./mpi_mm

echo "Rulare pi Calculation"
mpirun --mca btl_tcp_if_include eth0 -np 4 ./mpi_pi_send
