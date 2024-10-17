all:
	g++ -O3 -o main.out main.cpp
time:
	./time.sh
run:
	./main.out < samples/input_sample_1
all2:
	g++ -O3 -o main2.out main2.cpp
time2:
	./time2.sh
run2:
	./main2.out < samples/input_sample_1
all_alt:
	g++ -std=c++17 -O3 -o main_alt.out main_alt.cpp
time_alt:
	./time_alt.sh
run_alt:
	./main_alt.out < samples/input_sample_1
samples:
	mkdir samples
	cd samples
	python3 generator.py ./samples/input_sample_3 10000
	python3 generator.py ./samples/input_sample_4 100000
	python3 generator.py ./samples/input_sample_5 1000000
	python3 generator.py ./samples/input_sample_6 10000000
	cd ..
clean:
	rm -r samples
	rm *.out
