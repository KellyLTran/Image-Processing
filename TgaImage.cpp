
#include "TgaImage.h"
#include <fstream>
#include <iostream>
using namespace std;


TgaImage::TgaImage(int width, int height) {
    width_ = width;
    height_ = height;
    pixels_.resize(width_ * height_);
}

Header TgaImage::getHeader() const {
    return header_;
}

vector<unsigned char> TgaImage::getPixels() const {
    return pixels_;
}

int TgaImage::getWidth() const {
    return width_;
}

int TgaImage::getHeight() const {
    return height_;
}

void TgaImage::setHeader(const Header& header) {
    header_ = header;
}

void TgaImage::setPixels(vector<unsigned char> pixels) {
    pixels_ = pixels;
}

void TgaImage::setWidth(int width) {
    width_ = width;
}

void TgaImage::setHeight(int height) {
    height_ = height;
}

bool TgaImage::readHeader(const string& filename) {

    // Creates an ifstream object called file and opens the file passed in as filename in binary mode
    ifstream file(filename, ios::binary);

    // Returns false and prints an error message if the file fails to open
    if (file.is_open() == false) {
        cout << "Error: Failed to open file " << filename << endl;
        return false;
    }

    // Reads TGA header information from file and stores it in the header_ variable
    file.read(&header_.idLength, 1);
    file.read(&header_.colorMapType, 1);
    file.read(&header_.dataTypeCode, 1);
    file.read((char*)&header_.colorMapOrigin, 2);
    file.read((char*)&header_.colorMapLength, 2);
    file.read(&header_.colorMapDepth, 1);
    file.read((char*)&header_.xOrigin, 2);
    file.read((char*)&header_.yOrigin, 2);
    file.read((char*)&header_.width, 2);
    width_ = header_.width;
    file.read((char*)&header_.height, 2);
    height_ = header_.height;
    file.read(&header_.bitsPerPixel, 1);
    file.read(&header_.imageDescriptor, 1);
    file.close();
    return true;
}

bool TgaImage::read(const string& filename) {
    ifstream file(filename, ios::binary);
    if (file.is_open() == false) {
        cout << "Error: Failed to open file " << filename << endl;
        return false;
    }

    // Moves the read position of file 18 bytes from the beginning of the file to skip the header
    file.seekg(18, ios::beg);

    // Reads TGA pixel data from file and stores it in the pixels_ vector
    const int numPixels = width_ * height_;

    // Resizes by multiplying by 3 to account for RGB format of 3 different color channels
    pixels_.resize(numPixels * 3);

    // Uses reinterpret_cast to convert unsigned char* pointer to const char*
    file.read(reinterpret_cast<char*>(pixels_.data()), numPixels * 3);
    file.close();
    return true;
}

bool TgaImage::write(const string& filename)  {

    // Creates an ofstream object called file and opens the file passed in as filename in binary mode
    ofstream file(filename, ios::binary);
    if (file.is_open() == false) {
        cout << "Error: Failed to open file " << filename << endl;
        return false;
    }

    // Writes TGA header information to the file
    file.write(&header_.idLength, 1);
    file.write(&header_.colorMapType, 1);
    file.write(&header_.dataTypeCode, 1);
    file.write((const char*)&header_.colorMapOrigin, 2);
    file.write((const char*)&header_.colorMapLength, 2);
    file.write(&header_.colorMapDepth, 1);
    file.write((const char*)&header_.xOrigin, 2);
    file.write((const char*)&header_.yOrigin, 2);
    file.write((const char*)&header_.width, 2);
    file.write((const char*)&header_.height, 2);
    file.write(&header_.bitsPerPixel, 1);
    file.write(&header_.imageDescriptor, 1);

    // Writes TGA pixel data to the file
    const int numPixels = width_ * height_;
    file.write(reinterpret_cast<const char*>(pixels_.data()), numPixels * 3);
    file.close();
    return true;
}


unsigned char TgaImage::Multiply(unsigned char np1, unsigned char np2) {

    // Normalizes the pixel values by dividing them by 255.0, then multiplies them
    float norm1 = np1 / 255.0f;
    float norm2 = np2 / 255.0f;
    float result = norm1 * norm2;

    // Multiplies result by 255.0 and adds 0.5 to make and round a new pixel value
    result *= 255.0f;
    result += 0.5f;

    // Uses static_cast to convert result back to an unsigned char
    return static_cast<unsigned char>(result);
}

unsigned char TgaImage::Screen(unsigned char np1, unsigned char np2) {
    float norm1 = np1 / 255.0f;
    float norm2 = np2 / 255.0f;

    // Calculates the Screen value using the normalized values based on the channel formula
    float screenValue = 1.0f - ((1.0f - norm1) * (1.0f - norm2));
    screenValue *= 255.0f;
    screenValue += 0.5f;
    return static_cast<unsigned char>(screenValue);
}

unsigned char TgaImage::Subtract(unsigned char p1, unsigned char p2) {

    // Converts p1 and p2 to int to avoid overflow since int supports a large range of values
    int int1 = p1;
    int int2 = p2;

    // Subtracts the pixel values and clamps them to range [0,255] 
    // All values lower than zero become zero, and all values greater than 255 become 255
    int result = int1 - int2;
    if (result < 0) {
        result = 0;
    }
    else if (result > 255) {
        result = 255;
    }
    return static_cast<unsigned char>(result);
}

unsigned char TgaImage::Addition(int p1, int p2) {
    int int1 = p1;
    int int2 = p2;
    int result = int1 + int2;
    if (result < 0) {
        result = 0;
    }
    else if (result > 255) {
        result = 255;
    }
    return static_cast<unsigned char>(result);
}

unsigned char TgaImage::Overlay(unsigned char np1, unsigned char np2) {
    float norm1 = np1 / 255.0f;
    float norm2 = np2 / 255.0f;

    // Checks if NP2 <= 0.5 to calculate designated channel formula 
    if (norm2 <= 0.5f) {

        float overlayValue = 2.0f * norm1 * norm2;
        overlayValue *= 255.0f;
        overlayValue += 0.5f;
        if (overlayValue < 0) {
            overlayValue = 0;
        }
        else if (overlayValue > 255) {
            overlayValue = 255;
        }
        return static_cast<unsigned char>(overlayValue);
    }
    else {
        float overlayValue = 1.0f - (2.0f * (1.0f - norm1) * (1.0f - norm2));
        overlayValue *= 255.0f;
        overlayValue += 0.5f;
        if (overlayValue < 0) {
            overlayValue = 0;
        }
        else if (overlayValue > 255) {
            overlayValue = 255;
        }
        return static_cast<unsigned char>(overlayValue);
    }
}
