#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

int main(){

  ifstream image;
  ofstream newImage;

  image.open("./images/monument.ppm");
  newImage.open("newimage.ppm");

  // copy over header information
  string type = "", width = "", height = "", RGB = "";

  image >> type;
  image >> width;
  image >> height;
  image >> RGB;

  newImage << type << endl;
  newImage << width << " " << height << endl;
  newImage << RGB << endl;

  // cout << type << ' ' << width << ' ' << height << ' ' << RGB << '\n';	
  string red = "", green = "", blue = "";	
  int r = 0, g = 0, b = 0;
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

    b = min(b + 50, 255);

    newImage  << r << " " << g << " " << b << endl;
  }

  image.close();
  newImage.close();

  return 0;
}