# Gaussian blur filter for images in parallel with openMp

## How to run

To run the sequential code, run the following commands on the root folder:

```
make sequential
choose the name of the image e.g. star_field.ppm
```

To run the parallel code, run the following commands on the root folder:

```
make parallel
choose the number of threads e.g. 6
choose the name of the image e.g. star_field.ppm
```

Open the newimage.ppm file to see the result (you can use GIMP to visualize the .ppm image).
