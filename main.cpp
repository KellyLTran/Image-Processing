
#include "TgaImage.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;


bool MultiplyTwoImages(string topImageFilename, string bottomImageFilename, string outputImageFilename) {
    
    // Creates new object topImage and initializes the width and height to 0 so the header can be read before the image data loads
    TgaImage topImage(0, 0);
    if (topImage.readHeader(topImageFilename) == false) {
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }

    // Reads layer1.tga (top layer) with the read function
    topImage.read(topImageFilename);

    // Reads pattern1.tga (bottom layer) with the read function
    TgaImage bottomImage(0, 0);
    if (bottomImage.readHeader(bottomImageFilename) == false) {
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    bottomImage.read(bottomImageFilename);

    // Creates the output image with the same width and height as the input images
    TgaImage outputImage(topImage.getHeader().width, topImage.getHeader().height);

    // Sets the header of outputImage to match the header of the top layer image
    outputImage.setHeader(topImage.getHeader());

    // Gets the pixels from the top and bottom layer 
    vector<unsigned char> topPixels = topImage.getPixels();
    vector<unsigned char> bottomPixels = bottomImage.getPixels();
    vector<unsigned char> outputPixels;

    // Applies the Multiply blending mode to the two layers by multiplying each pixel in the top layer with the corresponding pixel of the bottom layer
    for (int i = 0; i < topPixels.size(); i++) {
        unsigned char np1 = topPixels[i];
        unsigned char np2 = bottomPixels[i];
        unsigned char result = topImage.Multiply(np1, np2);

        // Adds each result to the outputPixels vector
        outputPixels.push_back(static_cast<unsigned char>(result));
    }

    // Sets pixel data of outputImage to the outputPixels vector
    outputImage.setPixels(outputPixels);

    // Writes the output image to a file with the write function
    if (outputImage.write(outputImageFilename) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool SubtractTwoImages(string topImageFilename, string bottomImageFilename, string outputImageFilename) {
    
    // Reads layer2.tga (top layer)
    TgaImage topImage(0, 0);
    if (topImage.readHeader(topImageFilename) == false) {
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    topImage.read(topImageFilename);

    // Reads car.tga (bottom layer)
    TgaImage bottomImage(0, 0);
    if (bottomImage.readHeader(bottomImageFilename) == false) {
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    bottomImage.read(bottomImageFilename);

    TgaImage outputImage(topImage.getHeader().width, topImage.getHeader().height);
    outputImage.setHeader(topImage.getHeader());
    vector<unsigned char> topPixels = topImage.getPixels();
    vector<unsigned char> bottomPixels = bottomImage.getPixels();
    vector<unsigned char> outputPixels;

    // Applies the Subtract blending mode to the two layers
    for (int i = 0; i < topPixels.size(); i++) {
        unsigned char np1 = topPixels[i];
        unsigned char np2 = bottomPixels[i];
        unsigned char result = bottomImage.Subtract(np2, np1);
        outputPixels.push_back(static_cast<unsigned char>(result));
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputImageFilename) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool ScreenTwoImages(string topImageFilename, string bottomImageFilename, string outputImageFilename) {
    TgaImage topImage(0, 0);
    if (topImage.readHeader(topImageFilename) == false) {
        cout << "Error: Failed to read to the header of the image file." << endl;
        return false;
    }
    topImage.read(topImageFilename);

    TgaImage bottomImage(0, 0);
    if (bottomImage.readHeader(bottomImageFilename) == false) {
        cout << "Error: Failed to read to the header of the image file." << endl;
        return false;
    }
    bottomImage.read(bottomImageFilename);
    TgaImage outputImage(topImage.getHeader().width, topImage.getHeader().height);
    outputImage.setHeader(topImage.getHeader());
    vector<unsigned char> topPixels = topImage.getPixels();
    vector<unsigned char> bottomPixels = bottomImage.getPixels();
    vector<unsigned char> outputPixels;
    for (int i = 0; i < topPixels.size(); i++) {
        unsigned char np1 = topPixels[i];
        unsigned char np2 = bottomPixels[i];
        unsigned char result = bottomImage.Screen(np2, np1);
        outputPixels.push_back(static_cast<unsigned char>(result));
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputImageFilename) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool OverlayTwoImages(string topImageFilename, string bottomImageFilename, string outputImageFilename) {
    
    // Reads layer1.tga (top layer)
    TgaImage topImage(0, 0);
    if (topImage.readHeader(topImageFilename) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    topImage.read(topImageFilename);

    // Reads pattern1.tga (bottom layer)
    TgaImage bottomImage(0, 0);
    if (bottomImage.readHeader(bottomImageFilename) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    bottomImage.read(bottomImageFilename);
    TgaImage outputImage(topImage.getHeader().width, topImage.getHeader().height);
    outputImage.setHeader(topImage.getHeader());
    vector<unsigned char> topPixels = topImage.getPixels();
    vector<unsigned char> bottomPixels = bottomImage.getPixels();
    vector<unsigned char> outputPixels;

    // Applies the Overlay blending mode to the two layers
    for (int i = 0; i < topPixels.size(); i++) {
        unsigned char np1 = topPixels[i];
        unsigned char np2 = bottomPixels[i];
        unsigned char result = topImage.Overlay(np1, np2);
        outputPixels.push_back(static_cast<unsigned char>(result));
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputImageFilename) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool AddGreen(string inputFile, int number, string outputFile) {
    TgaImage carImage(0, 0);
    if (carImage.readHeader(inputFile) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    carImage.read(inputFile);
    TgaImage outputImage(carImage.getHeader().width, carImage.getHeader().height);
    outputImage.setHeader(carImage.getHeader());

    // Adds 200 to the green channel of each pixel
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> outputPixels;
    for (int i = 0; i < pixels.size(); i += 3) {
        outputPixels.push_back(pixels[i]);
        int green = outputImage.Addition(pixels[i + 1], number);
        outputPixels.push_back(static_cast<unsigned char>(green));
        outputPixels.push_back(pixels[i + 2]);
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool AddRed(string inputFile, int number, string outputFile) {
    TgaImage carImage(0, 0);
    if (carImage.readHeader(inputFile) == false) {
        cout << "Error: Failed to read to the header of the image file." << endl;
        return false;
    }
    carImage.read(inputFile);
    TgaImage outputImage(carImage.getHeader().width, carImage.getHeader().height);
    outputImage.setHeader(carImage.getHeader());
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> outputPixels;
    for (int i = 0; i < pixels.size(); i += 3) {     
        outputPixels.push_back(pixels[i]);
        outputPixels.push_back(pixels[i+1]);
        int red = outputImage.Addition(pixels[i + 2], number);
        outputPixels.push_back(static_cast<unsigned char>(red));
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool AddBlue(string inputFile, int number, string outputFile) {
    TgaImage carImage(0, 0);
    if (carImage.readHeader(inputFile) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    carImage.read(inputFile);
    TgaImage outputImage(carImage.getHeader().width, carImage.getHeader().height);
    outputImage.setHeader(carImage.getHeader());
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> outputPixels;
    for (int i = 0; i < pixels.size(); i += 3) {
        int blue = outputImage.Addition(pixels[i], number);
        outputPixels.push_back(static_cast<unsigned char>(blue));
        outputPixels.push_back(pixels[i + 1]);
        outputPixels.push_back(pixels[i + 2]);
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool ScaleRed(string inputFile, int number, string outputFile) {
    TgaImage carImage(0, 0);
    if (carImage.readHeader(inputFile) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    carImage.read(inputFile);
    TgaImage outputImage(carImage.getHeader().width, carImage.getHeader().height);
    outputImage.setHeader(carImage.getHeader());
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> outputPixels;

    // Gets the values of the blue, green, and red channels of the current pixel
    for (int i = 0; i < pixels.size(); i += 3) {
        unsigned char blue = pixels[i];
        unsigned char green = pixels[i + 1];
        unsigned char red = pixels[i + 2];

        // Initializes variables to store the new values of the red and blue channels
        float newRed = 0.0;
        if (i % 3 == 0) {
            newRed = red * number;
            if (newRed > 255) {
                newRed = 255;
            }
        }
        outputPixels.push_back(blue);
        outputPixels.push_back(green);
        outputPixels.push_back(static_cast<unsigned char>(newRed));
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool CombineThreeImages(string redLayer, string greenLayer, string blueLayer, string outputFile) {
    TgaImage redLayerImage(0, 0);
    if (redLayerImage.readHeader(redLayer) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    redLayerImage.read(redLayer);
    TgaImage greenLayerImage(0, 0);
    if (greenLayerImage.readHeader(greenLayer) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    greenLayerImage.read(greenLayer);
    TgaImage blueLayerImage(0, 0);
    if (blueLayerImage.readHeader(blueLayer) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    blueLayerImage.read(blueLayer);
    TgaImage outputImage(redLayerImage.getHeader().width, redLayerImage.getHeader().height);
    outputImage.setHeader(redLayerImage.getHeader());

    // Combines the layers into the output image
    vector<unsigned char> redPixels = redLayerImage.getPixels();
    vector<unsigned char> greenPixels = greenLayerImage.getPixels();
    vector<unsigned char> bluePixels = blueLayerImage.getPixels();
    vector<unsigned char> outputPixels;
    for (int i = 0; i < redPixels.size(); i += 3) {
        // Adds the blue, green, and red values for each pixel
        outputPixels.push_back(bluePixels[i]);
        outputPixels.push_back(greenPixels[i]);
        outputPixels.push_back(redPixels[i]);
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool ScaleGreen(string inputFile, int number, string outputFile) {
    TgaImage carImage(0, 0);
    if (carImage.readHeader(inputFile) == false) { 
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    carImage.read(inputFile);
    TgaImage outputImage(carImage.getHeader().width, carImage.getHeader().height);
    outputImage.setHeader(carImage.getHeader());
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> outputPixels;
    for (int i = 0; i < pixels.size(); i += 3) {
        unsigned char blue = pixels[i];
        unsigned char green = pixels[i + 1];
        unsigned char red = pixels[i + 2];
        float newGreen = 0.0;
        if (i % 3 == 0) {
            newGreen = green * number;
            if (newGreen > 255) {
                newGreen = 255;
            }
        }
        outputPixels.push_back(blue);
        outputPixels.push_back(static_cast<unsigned char>(newGreen));
        outputPixels.push_back(red);
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool ScaleBlue(string inputFile, int number, string outputFile) {
    TgaImage carImage(0, 0); 
    if (carImage.readHeader(inputFile) == false) {
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    carImage.read(inputFile);
    TgaImage outputImage(carImage.getHeader().width, carImage.getHeader().height);
    outputImage.setHeader(carImage.getHeader());
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> outputPixels;
    for (int i = 0; i < pixels.size(); i += 3) {
        unsigned char blue = pixels[i];
        unsigned char green = pixels[i + 1];
        unsigned char red = pixels[i + 2];

        float norm1 = blue / 255.0f;
        float norm2 = number;
        float newBlue = norm1 * norm2;

        // Multiplies result by 255.0 and adds 0.5 to make and round a new pixel value
        newBlue *= 255.0f;
        newBlue += 0.5f;
        if (newBlue > 255) {
            newBlue = 255;
        }
        outputPixels.push_back(static_cast<unsigned char>(newBlue));
        outputPixels.push_back(green);
        outputPixels.push_back(red);
    }
    
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool OnlyBlue(string inputFile, string outputFile) {
    TgaImage carImage(0, 0);
    if (carImage.readHeader(inputFile) == false) {
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    carImage.read(inputFile);
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> redPixels, greenPixels, bluePixels;
    for (int i = 0; i < pixels.size(); i += 3) {
        redPixels.push_back(pixels[i + 2]);
        redPixels.push_back(pixels[i + 2]);
        redPixels.push_back(pixels[i + 2]);
        greenPixels.push_back(pixels[i + 1]);
        greenPixels.push_back(pixels[i + 1]);
        greenPixels.push_back(pixels[i + 1]);
        bluePixels.push_back(pixels[i]);
        bluePixels.push_back(pixels[i]);
        bluePixels.push_back(pixels[i]);
    }
    TgaImage blueImage(carImage.getHeader().width, carImage.getHeader().height);
    blueImage.setHeader(carImage.getHeader());
    blueImage.setPixels(bluePixels);

    if (blueImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}

bool OnlyRed(string inputFile, string outputFile) {
    TgaImage carImage(0, 0); 
    if (carImage.readHeader(inputFile) == false) { 
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    carImage.read(inputFile);
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> redPixels, greenPixels, bluePixels;
    for (int i = 0; i < pixels.size(); i += 3) {
        redPixels.push_back(pixels[i + 2]);
        redPixels.push_back(pixels[i + 2]);
        redPixels.push_back(pixels[i + 2]);
        greenPixels.push_back(pixels[i + 1]);
        greenPixels.push_back(pixels[i + 1]);
        greenPixels.push_back(pixels[i + 1]);
        bluePixels.push_back(pixels[i]);
        bluePixels.push_back(pixels[i]);
        bluePixels.push_back(pixels[i]);
    }
    TgaImage redImage(carImage.getHeader().width, carImage.getHeader().height);
    redImage.setHeader(carImage.getHeader());
    redImage.setPixels(redPixels);
    if (redImage.write(outputFile) == false) {
        cout << "Error: Failed to write the red channel image to a file." << endl;
        return false;
    }
    return true;
}

bool OnlyGreen(string inputFile, string outputFile) {
    TgaImage carImage(0, 0); 
    if (carImage.readHeader(inputFile) == false) { 
        cout << "Error: Failed to read the header of the image file." << endl;
        return false;
    }
    carImage.read(inputFile);
    vector<unsigned char> pixels = carImage.getPixels();
    vector<unsigned char> redPixels, greenPixels, bluePixels;
    for (int i = 0; i < pixels.size(); i += 3) {
        redPixels.push_back(pixels[i + 2]);
        redPixels.push_back(pixels[i + 2]);
        redPixels.push_back(pixels[i + 2]);
        greenPixels.push_back(pixels[i + 1]);
        greenPixels.push_back(pixels[i + 1]);
        greenPixels.push_back(pixels[i + 1]);
        bluePixels.push_back(pixels[i]);
        bluePixels.push_back(pixels[i]);
        bluePixels.push_back(pixels[i]);
    }
    TgaImage greenImage(carImage.getHeader().width, carImage.getHeader().height);
    greenImage.setHeader(carImage.getHeader());
    greenImage.setPixels(greenPixels);
    if (greenImage.write(outputFile) == false) {
        cout << "Error: Failed to write the green channel image to a file" << endl;
        return false;
    }
    return true;
}

bool Flip(string inputFile, string outputFile) {
    TgaImage textImage(0, 0);
    if (textImage.readHeader(inputFile) == false) {
        cout << "Error: Failed to read to the header of the image file."  << endl;
        return false;
    }
    textImage.read(inputFile);
    TgaImage outputImage(textImage.getHeader().width, textImage.getHeader().height);
    outputImage.setHeader(textImage.getHeader());

    // Rotates the image by 180 degrees
    // Calculates the number of bytes per pixel
    int bytesPerPixel = textImage.getHeader().bitsPerPixel / 8; 
    vector<unsigned char> pixels = textImage.getPixels();

    // Creates a new vector to hold the rotated pixel data
    vector<unsigned char> outputPixels; 

    // Loops through each row then each column with both in reverse order
    for (int y = textImage.getHeader().height - 1; y >= 0; --y) {
        for (int x = textImage.getHeader().width - 1; x >= 0; --x) {

            // Calculates the index of the current pixel
            int index = (y * textImage.getHeader().width + x) * bytesPerPixel; 

            // Loops through each byte in the current pixel and copies byte from original image to the output image
            for (int i = 0; i < bytesPerPixel; ++i) { 
                outputPixels.push_back(pixels[index + i]); 
            }
        }
    }
    outputImage.setPixels(outputPixels);
    if (outputImage.write(outputFile) == false) {
        cout << "Error: Failed to write to the output file." << endl;
        return false;
    }
    return true;
}


// Passes an int parameter argc (argument count) to main() for the number of command-line arguments
// Passes a second parameter argv (argument vector) to main(), defined as an array with a string for each command-line argument
int main(int argc, char* argv[]) {

// Creates the output directory if it does not exist for windows
#ifdef _WIN32
    system("if not exist output mkdir output");

// For non-windows 
#else
    system("mkdir -p output");
#endif

    // Checks if argv[1] input matches the string "--help" with the strcmp function
    if (argc == 1 or strcmp(argv[1], "--help") == 0) {
        cout << "Project 2: Image Processing, Spring 2023" << endl << endl;
        cout << "Usage:" << endl;
        cout << "\t" << argv[0] << " [output] [firstImage] [method] [...]" << endl;
        return 0;
    }

    // Checks if filename is valid by seeing if it ends with ".tga"
    string outputFilename = argv[1];
    if (outputFilename.empty() or (outputFilename.size() < 4) or outputFilename.substr(outputFilename.size() - 4) != ".tga") {
        cout << "Invalid file name." << endl;
        return 0;
    }

    string inputFilename = "";
    if (argc >= 3) {
        inputFilename = argv[2];
        if (inputFilename.empty() or inputFilename.substr(inputFilename.size() - 4) != ".tga") {
            cout << "Invalid file name." << endl;
            return false;
        }
        ifstream inputFile(inputFilename);
        if (inputFile.fail()) {
            cout << "File does not exist." << endl;
            return false;
        }
        inputFile.close();
    }
    else
    {
        cout << "Invalid file name." << endl;
        return false;
    }

    string methodName = "";
    if (argc >= 4) {
        methodName = argv[3];
        if (methodName != "combine" && methodName != "screen" && methodName != "addred" && methodName != "onlyred" &&
            methodName != "multiply" && methodName != "addgreen" && methodName != "onlygreen" && methodName != "subtract" &&
            methodName != "addblue" && methodName != "onlyblue" && methodName != "overlay" && methodName != "scalered" &&
            methodName != "scalegreen" && methodName != "scaleblue" && methodName != "flip") {
            cout << "Invalid method name." << endl;
            return false;
        }
    }

    for (int i = 3; i < argc; i++) {
        string methodArg;
        string methodArg2;
        if (methodName == "multiply") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            if (methodArg.empty() or methodArg.substr(methodArg.size() - 4) != ".tga") {
                cout << "Invalid argument, invalid file name." << endl;
                return false;
            }
            ifstream argFile(methodArg);
            if (argFile.fail()) {
                cout << "Invalid argument, file does not exist." << endl;
                return false;
            }
     
            // Calls MultiplyTwoImages to multiply inputFilename and methodArg1
            if (MultiplyTwoImages(inputFilename, methodArg, outputFilename))
            {
                if (i == 3) {
                    cout << "Multiplying " << inputFilename << " and " << methodArg << " ..." << endl;
                }
                else {
                    cout << "... and multiplying " << methodArg << " to previous step ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to multiply the two files. " << inputFilename << " and " << methodArg << endl;
            }
            argFile.close();
        }

        else if ((methodName == "screen") or (methodName == "subtract")) {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            if (methodArg.empty() or methodArg.substr(methodArg.size() - 4) != ".tga") {
                cout << "Invalid argument, invalid file name." << endl;
                return false;
            }
            ifstream argFile(methodArg);
            if (argFile.fail()) {
                cout << "Invalid argument, file does not exist." << endl;
                return false;
            }
   
            // Calls SubtractTwoImages to multiply inputFilename and methodArg1
            if (methodName == "subtract") {
                if (i == 3) {
                    if (SubtractTwoImages(methodArg, inputFilename, outputFilename)) {
                        cout << "Subtracting " << inputFilename << " from " << methodArg << " ..." << endl;
                    }
                    else {
                        cout << "Error: Failed to substract the two files. " << inputFilename << " and " << methodArg << endl;
                    }
                }
                else {
                    if (SubtractTwoImages(methodArg, inputFilename, outputFilename)) {
                        cout << "... and subtracting " << methodArg << " from previous step ... " << endl;
                    }
                    else {
                        cout << "Error: Failed to substract the two files. " << inputFilename << " and " << methodArg << endl;
                    }
                }
            }
            else {
                if (ScreenTwoImages(inputFilename, methodArg, outputFilename)) {
                    if (i == 3) {
                        cout << "Subtracting " << inputFilename << " from " << methodArg << " ..." << endl;
                    }
                    else {
                        cout << "... and subtracting " << methodArg << " from previous step ... " << endl;
                    }
                }
                else {
                    cout << "Error: Failed to substract the two files. " << inputFilename << " and " << methodArg << endl;
                }
            }
            argFile.close();
        }
        else if (methodName == "overlay") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            if (methodArg.empty() or methodArg.substr(methodArg.size() - 4) != ".tga") {
                cout << "Invalid argument, invalid file name." << endl;
                return false;
            }
            ifstream argFile(methodArg);
            if (argFile.fail()) {
                cout << "Invalid argument, file does not exist." << endl;
                return false;
            }

            if (OverlayTwoImages(inputFilename, methodArg, outputFilename))
            {
                if (i == 3) {
                    cout << "Overlaying " << inputFilename << " with " << methodArg << " ..." << endl;
                }
                else {
                    cout << "... and overlaying " << methodArg << " with previous step ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to overlay the two files. " << inputFilename << " and " << methodArg << endl;
            }
            argFile.close();
        }
        else if (methodName == "combine") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            if (methodArg.empty() or methodArg.substr(methodArg.size() - 4) != ".tga") {
                cout << "Invalid argument, invalid file name." << endl;
                return false;
            }
            ifstream argFile(methodArg);
            if (argFile.fail()) {
                cout << "Invalid argument, file does not exist." << endl;
                return false;
            }
            if (i + 2 < argc) {
                methodArg2 = argv[i + 2];
                i++;
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            if (methodArg2.empty() or methodArg2.substr(methodArg2.size() - 4) != ".tga") {
                cout << "Invalid argument, invalid file name." << endl;
                return false;
            }
            ifstream argFile2(methodArg2);
            if (argFile2.fail()) {
                cout << "Invalid argument, file does not exist." << endl;
                return false;
            }           
            if (CombineThreeImages(inputFilename, methodArg, methodArg2, outputFilename)) {
                if (i == 3) {
                    cout << "Combining " << inputFilename << " with " << methodArg << " ..." << endl;
                }
                else {
                    cout << "... and combining " << methodArg << " with previous step ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to combining the two files. " << inputFilename << " and " << methodArg << endl;
            }
            argFile.close();
            argFile2.close();
        }
        else if (methodName == "addgreen") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            int number;
            try {
                number = stoi(methodArg);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
                return false;
            }
            if (AddGreen(inputFilename, number, outputFilename)) {
                if (i == 3) {
                    cout << "Adding + " << number << " to green channel of " << inputFilename << " ..." << endl;
                }
                else {

                    cout << "... and adding + " << number << " to green channel of previous step ..." << endl;
                }
            }
            else {
                cout << "Error: Failed to add to the green channel. " << inputFilename << " by " << number << endl;
            }
        }
        else if (methodName == "addred") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            int number;
            try {
                number = stoi(methodArg);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
                return false;
            }

            if (AddRed(inputFilename, number, outputFilename)) {
                if (i == 3) {
                    cout << "Adding + " << number << " to red channel of " << inputFilename << " ..." << endl;
                }
                else {

                    cout << "... and adding + " << number << " to red channel of previous step ..." << endl;
                }
            }
            else {
                cout << "Error: Failed to add to the red channel. " << inputFilename << " by " << number << endl;
            }
        }
        else if (methodName == "addblue") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            int number;
            try {
                number = stoi(methodArg);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
                return false;
            }

            if (AddBlue(inputFilename, number, outputFilename))
            {
                if (i == 3) {
                    cout << "Adding + " << number << " to blue channel of " << inputFilename << " ..." << endl;
                }
                else {

                    cout << "... and adding + " << number << " to blue channel of previous step ..." << endl;
                }
            }
            else {
                cout << "Error: Failed to add to the blue channel. " << inputFilename << " by " << number << endl;
            }
        }
        else if (methodName == "scalegreen") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            int number;
            try {
                number = stoi(methodArg);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
                return false;
            }

            if (ScaleGreen(inputFilename, number, outputFilename))
            {
                if (i == 3) {
                    cout << "Scaling the green channel of " << inputFilename << " by " << number << " ..." << endl;
                }
                else {

                    cout << "... and scaling the green channel of previous step by " << number << " ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to scale the green channel. " << inputFilename << " by " << number << endl;
            }
        }
        else if (methodName == "scalered") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            int number;
            try {
                number = stoi(methodArg);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
                return false;
            }

            if (ScaleRed(inputFilename, number, outputFilename))
            {
                if (i == 3) {
                    cout << "Scaling the red channel of " << inputFilename << " by " << number << " ..." << endl;
                }
                else {
                    cout << "... and scaling the red channel of previous step by " << number << " ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to scale the red channel. " << inputFilename << " by " << number << endl;
            }
        }
        else if (methodName == "scaleblue") {
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (i + 1 < argc) {
                methodArg = argv[i + 1];
            }
            else {
                cout << "Missing argument." << endl;
                return false;
            }
            int number;
            try {
                number = stoi(methodArg);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
                return false;
            }
            if (ScaleBlue(inputFilename, number, outputFilename))
            {
                if (i == 3) {
                    cout << "Scaling the blue channel of " << inputFilename << " by " << number << " ..." << endl;
                }
                else {
                    cout << "... and scaling the blue channel of previous step by " << number << " ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to scale the blue channel. " << inputFilename << " by " << number << endl;
            }
        }
        else if (methodName == "onlyred") {
            if (argc < 4) {
                cout << "Missing argument." << endl;
                return false;
            }

            if (OnlyRed(inputFilename, outputFilename)) {
                if (i == 3) {
                    cout << "Separating the red channel of " << inputFilename << " ..." << endl;
                }
                else {

                    cout << "... and separting the red channel of previous output ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to seperate the red channel. " << inputFilename << endl;
            }
        }
        else if (methodName == "onlygreen") {
            if (argc < 4) {
                cout << "Missing argument." << endl;
                return false;
            }

            if (OnlyGreen(inputFilename, outputFilename))
            {
                if (i == 3) {
                    cout << "Separating the green channel of " << inputFilename << " ..." << endl;
                }
                else {
                    cout << "... and separting the green channel of previous output ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to separate the green channel. " << inputFilename << endl;
            }
        }
        else if (methodName == "onlyblue") {
            if (argc < 4) {
                cout << "Missing argument." << endl;
                return false;
            }

            if (OnlyBlue(inputFilename, outputFilename))
            {
                if (i == 3) {
                    cout << "Separating the blue channel of " << inputFilename << " ..." << endl;
                }
                else {
                    cout << "... and separting the blue channel of previous output ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to seperate the blue channel. " << inputFilename << endl;
            }
        }
        else if (methodName == "flip") {
            if (argc < 4) {
                cout << "Missing argument." << endl;
                return false;
            }
            if (Flip(inputFilename, outputFilename)) {
                if (i == 3) {
                    cout << "Flipping " << inputFilename << " ..." << endl;
                }
                else {
                    cout << "... and flipping output of previous step ... " << endl;
                }
            }
            else {
                cout << "Error: Failed to flip. " << inputFilename << endl;
            }
        }

        // Sets the output to be the input of the next method
        inputFilename = outputFilename; 
        if (methodName == "onlyred" or methodName == "onlygreen" or methodName == "onlyblue" or methodName == "flip") {
            if (i + 1 < argc) {
                methodName = argv[i + 1];
            }
        }
        else {
            if (i + 2 < argc) {
                methodName = argv[i + 2];
            }
            i++;
        }
        if (methodName != "combine" && methodName != "screen" && methodName != "addred" && methodName != "onlyred" &&
            methodName != "multiply" && methodName != "addgreen" && methodName != "onlygreen" && methodName != "subtract" &&
            methodName != "addblue" && methodName != "onlyblue" && methodName != "overlay" && methodName != "scalered" &&
            methodName != "scalegreen" && methodName != "scaleblue" && methodName != "flip") {
            cout << "Invalid method name." << endl;
            return false;
        }
    }
    cout << "... and saving output to " << outputFilename << endl;
    return 0;
}