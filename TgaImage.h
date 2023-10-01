
// Ensures that header file contents are only included once with header file guards
#ifndef TGA_IMAGE_H
#define TGA_IMAGE_H
#include <string>
#include <vector>
using namespace std;


// Declares Header structure
struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

class TgaImage {
public:
    // Declares the parametrized constructor 
    TgaImage(int width, int height);

    // Declares getter and setter functions for the header, pixels, width, and height
    Header getHeader() const;
    vector<unsigned char> getPixels() const;
    int getWidth() const;
    int getHeight() const;
    void setHeader(const Header& header);
    void setPixels(vector<unsigned char> pixels);
    void setWidth(int width);
    void setHeight(int height);

    // Declares functions for Part 1: Reading and Writing with a TGA filename as the parameter 
    bool read(const string& filename);
    bool write(const string& filename);
    bool readHeader(const string& filename);

    // Declares functions for Part 2: Image Manipulations with pixel values and normalized pixel values as parameters
    unsigned char Multiply(unsigned char np1, unsigned char np2);
    unsigned char Screen(unsigned char np1, unsigned char np2);
    unsigned char Subtract(unsigned char p1, unsigned char p2);
    unsigned char Addition(int p1, int p2);
    unsigned char Overlay(unsigned char np1, unsigned char np2);
       
private:
    int width_;
    int height_;
    Header header_;
    vector<unsigned char> pixels_;
    vector <unsigned char> overallImage_;  
};

// Ensures that code between #ifndef and #endif processes only if TGA_IMAGE_H is not defined
#endif
