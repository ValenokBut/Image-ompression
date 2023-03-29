#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "geometry.h"

const int width    = 1024;
const int height   = 768;

std::vector<Vec3f> framebuffer(width*height);
std::vector<Vec3f> framebuffer2(width*height);
std::vector<Vec3f> framebuffer3(width*height);

int limit(int x){
  if(x < 0)
    x = 0;
  else if(x > 255)
    x = 255;
  return x;
}

void render2() {
    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./out2.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height*width; ++i) {
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(limit(framebuffer3[i][j]));
        }
    }
    ofs.close();
}


void render() {

    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            framebuffer[i+j*width] = Vec3f(j/float(height),i/float(width), 0);
        }
    }

    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./out.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height*width; ++i) {
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

int main() {
    render();
    int kk;
    float a = 0;
    float b = 0;
    scanf("%d", &kk);
    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            framebuffer2[i+j*width].x = framebuffer[i+j*width].x * 0.299 + framebuffer[i+j*width].y * 0.578 + framebuffer[i+j*width].z * 0.114;
          framebuffer2[i+j*width].y = framebuffer[i+j*width].x * 0.1678 - framebuffer[i+j*width].y * 0.3313 + framebuffer[i+j*width].z * 0.5;
          framebuffer2[i+j*width].z = framebuffer[i+j*width].x * 0.5 - framebuffer[i+j*width].y * 0.4187 + framebuffer[i+j*width].z * 0.0813;
        }
    }

    for (size_t j = 0; j<height; j+=kk) {
        for (size_t i = 0; i<width; i+=kk) {
          if ((i + kk < width) && (j + kk < width)){
              for (size_t j1 = j; j1 < j + kk; j1++) {
                for (size_t i1 = i; i1<i + kk; i1++) {
                  a = a + framebuffer2[i1+j1*width].y;
                  b = b + framebuffer2[i1+j1*width].z;
                }}
           // a = 0.25 * (framebuffer2[i+j*width].y + framebuffer2[(i +1)+j*width].y +framebuffer2[i+(j + 1)*width].y + framebuffer2[(i+1)+(j+1)*width].y);
           // b = 0.25 * (framebuffer2[i+j*width].z + framebuffer2[(i +1)+j*width].z +framebuffer2[i+(j + 1)*width].z + framebuffer2[(i+1)+(j+1)*width].z);
            a = a / (kk * kk);
            b = b / (kk * kk);
            for (size_t j1 = j; j1 < j + kk; j1++) {
                for (size_t i1 = i; i1<i + kk; i1++) {
                  framebuffer2[i1+j1*width].y = a * 255;
                  framebuffer2[i1+j1*width].z = b * 255;
                  framebuffer2[i1+j1*width].x *= 255;
                }}
        }
        }
        }

  for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            framebuffer3[i+j*width].x = limit(framebuffer2[i+j*width].x + 1.402 * (framebuffer2[i+j*width].x-128));
          framebuffer3[i+j*width].y = limit(framebuffer2[i+j*width].x - 0.344136 * (framebuffer2[i+j*width].y-128) - 0.714136 * (framebuffer2[i+j*width].z-128));
          framebuffer3[i+j*width].z = limit(framebuffer2[i+j*width].x + 1.772 * (framebuffer2[i+j*width].y - 128));
        }
    }
  render2();
  //r[i] = limit((int)y[i] + 1.402 * ((int)cr[i]-128));
  //g[i] = limit((int)y[i] - 0.344136 * ((int)cb[i]-128) - 0.714136 * ((int)cr[i]-128));
  //b[i] = limit((int)y[i] + 1.772 * ((int)cb[i]-128));
    return 0;
}