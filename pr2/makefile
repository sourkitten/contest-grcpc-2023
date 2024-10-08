all:
	g++ -O3 -o main.out main.cpp
time:
	./time.sh
run:
	./main.out < samples/input_sample_1
debug:
	g++ -DDEBUG -O3 -o main.out main.cpp
sample:
	python3 generator.py 1000000 1000000 100 > samples/input_sample_2
