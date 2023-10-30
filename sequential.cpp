#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>

using namespace std;

struct Pixel{
  float r, g, b;
  Pixel(float r, float g, float b) : r(r), g(g), b(b) {}
};

// Gaussian blur function for RGB image
vector<Pixel> gaussian_blur(int width, int height, vector<Pixel>& input, int radius) {
    vector<Pixel> output;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
            float weight_sum = 0.0;
            for (int j = -radius; j <= radius; j++) {
                for (int i = -radius; i <= radius; i++) {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        float weight = exp(-(i * i + j * j) / (2.0 * radius * radius));
                        Pixel currentPixel = input[ny * width + nx];
                        sum_r += currentPixel.r * weight;
                        sum_g += currentPixel.g * weight;
                        sum_b += currentPixel.b * weight;
                        weight_sum += weight;
                    }
                }
            }
            output.push_back(Pixel(sum_r / weight_sum, sum_g / weight_sum, sum_b / weight_sum));
        }
    }

    return output;
}


int main(){

  ifstream image;
  ofstream newImage;

  // Open the image
  image.open("./images/skylight.ppm");
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

  // apply gaussian blur
  vector<Pixel> filtered = gaussian_blur(stoi(width), stoi(height), pixels, 5);

  // write the new image
  for (int i = 0; i < filtered.size(); i++) {
    newImage << filtered[i].r << " " << filtered[i].g << " " << filtered[i].b << endl;
  }

  image.close();
  newImage.close();

  return 0;
}