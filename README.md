# Genetic Algorithm for Traveling Salesman Problem

This code presents a powerful genetic algorithm (GA) for solving the traveling salesman problem (TSP).

To construct a powerful GA, I use edge swapping(ES) with a local search procedure to determine good combinations of building blocks of parent solutions for generating even better offspring solutions.

Experimental results on well studied TSP benchmarks demonstrate that the proposed GA is competitive in finding very high quality solutions on instances with about 15,000 cities.

## How to run
1. go to ./src directory:
cd src

2. run bash file run.sh and choose one of the five predefined TSP map as input:
sudo bash run.sh

3. checkout TSP route in bestSolution.txt:
vi bestSolution.txt