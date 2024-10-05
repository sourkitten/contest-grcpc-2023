all:
	g++ -O3 -o main.out main.cpp
time:
	./time.sh
run:
	./main.out < samples/input_sample_1
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
