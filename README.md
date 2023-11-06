# Gaussian blur filter for images in parallel with openMp

## How to run

To run the sequential code, run the following commands:

```
g++ sequential.cpp -O0
./a.out
```

To run the parallel code, run the following commands:

```
g++ parallel.cpp -O0 -fopenmp
./a.out
```

Open the newimage.ppm file to see the result (you can use GIMP to visualize the .ppm image).
