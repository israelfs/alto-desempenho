#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <chrono>

using namespace std;

struct Pixel{ // struct to hold RGB values
  float r, g, b;
  Pixel(float r, float g, float b) : r(r), g(g), b(b) {}
};

// Gaussian blur function for RGB image
vector<Pixel> gaussian_blur(int width, int height, vector<Pixel>& input, int radius) {
    vector<Pixel> output; // initialize output image to all black

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
            float weight_sum = 0.0;
            // loop over all pixels in the kernel
            for (int j = -radius; j <= radius; j++) {
                for (int i = -radius; i <= radius; i++) {
                    int nx = x + i;
                    int ny = y + j;
                    // only sum the pixel if it's within the image bounds
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        // calculate the gaussian weight
                        float weight = exp(-(i * i + j * j) / (2.0 * radius * radius));
                        Pixel currentPixel = input[ny * width + nx];
                        sum_r += currentPixel.r * weight;
                        sum_g += currentPixel.g * weight;
                        sum_b += currentPixel.b * weight;
                        weight_sum += weight;
                    }
                }
            }
            // normalize the pixel value
            output.push_back(Pixel(sum_r / weight_sum, sum_g / weight_sum, sum_b / weight_sum));
        }
    }

    return output;
}


int main(int argc, char *argv[]) {

  // time_t start, end;

  ifstream image;
  ofstream newImage;

  // Digite a imagem que você queira abrir
  cout << "Digite a imagem que você queira abrir: ";
  string img;
  cin >> img;

  // Open the image
  image.open("./images/" + img);
  // Open a new image to write to
  newImage.open("newimage.ppm");

  // copy over header information
  string type = "", width = "", height = "", RGB = "";

  image >> type;
  image >> width;
  image >> height;
  image >> RGB;

  // set the header information for the new image
  newImage << type << endl;
  newImage << width << " " << height << endl;
  newImage << RGB << endl;

  string red = "", green = "", blue = "";	
  int r = 0, g = 0, b = 0;
  
  vector<Pixel> pixels;

  while(!image.eof()){
    // read in the RGB values
    image >> red;
    image >> green; 
    image >> blue;

    stringstream redstream(red);
    stringstream greenstream(green);
    stringstream bluestream(blue);
    // convert to int
    redstream >> r;
    greenstream >> g;
    bluestream >> b;

    pixels.push_back(Pixel(r, g, b));
  }

   // start timer
  // time(&start); 
  auto start = std::chrono::high_resolution_clock::now();

  // apply gaussian blur
  vector<Pixel> filtered = gaussian_blur(stoi(width), stoi(height), pixels, 5);

  // Recording end time. 
  // time(&end);
  auto end = std::chrono::high_resolution_clock::now();

  // double time_taken = end - start;
  double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  cout << "Time taken by the sequential program is: " << fixed << time_taken/1000 << " sec " << endl;

  // write the new image
  for (int i = 0; i < filtered.size(); i++) {
    newImage << filtered[i].r << " " << filtered[i].g << " " << filtered[i].b << endl;
  }

  image.close();
  newImage.close();


  time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


  return 0;
}