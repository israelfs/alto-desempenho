sequential:
	g++ sequential.cpp -o sequential

parallel:
	g++ parallel.cpp -o parallel -fopenmp

clean:
	rm -f sequential parallel newimage.ppm