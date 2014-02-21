All: knapsack xmax dp_knapsack

knapsack: knapsack.cc 
	g++ -Wall -g knapsack.cc -o knapsack

xmax: main.cc
	g++ -Wall -g main.cc -o xmax

dp_knapsack:
	g++ -g dp_knapsack.cc -o dp_knapsack