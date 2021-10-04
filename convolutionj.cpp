#include <iostream>
#include <fstream>
#include <string>


#define DATASIZE 375000
#define WIDTH 750
#define HEIGHT 500
FILE* source_file_id, * output_file_id;
unsigned char data[DATASIZE], outdata[DATASIZE];
int x, y;
int filter[9] = { -1, -2, -3, -4, 0, 4, 3, 2, 1 };

void perform_convolution() {
    // std::cout << "Not implemented!" << std::endl;
    int kCols;
    int kRows;
    int rows;
    int cols;
    int kCenterX = kCols / 2;
    int kCenterY = kRows / 2;

    for(int i=0; i < rows; ++i)              // rows
    {
        for(int j=0; j < cols; ++j)          // columns
        {
            for(int m=0; m < kRows; ++m)     // kernel rows
            {
                int mm = kRows - 1 - m;      // row index of flipped kernel

                for(int n=0; n < kCols; ++n) // kernel columns
                {
                    int nn = kCols - 1 - n;  // column index of flipped kernel

                    // index of input signal, used for checking boundary
                    int ii = i + (kCenterY - mm);
                    int jj = j + (kCenterX - nn);
        
                    // ignore input samples which are out of bound
                    if( ii >= 0 && ii < rows && jj >= 0 && jj < cols )
                        outdata += data[ii][jj] * filter[mm][nn];
                }
            }
        }
    }
}



int main(int argc, char** argv)
{
    std::cout << "Main Entered..." << std::endl << std::endl;

    std::string sourceFilename = "unesco750-1.raw";
    std::string outputFilename = "output.raw";

    std::cout << "Opening '" << sourceFilename << "' for reading." << std::endl;

    source_file_id = fopen(sourceFilename.c_str(), "r");
    fread(data, 1, DATASIZE, source_file_id);
    fclose(source_file_id);

    // setup


    std::cout << std::endl << "Beginning convolution" << std::endl;
    // convolution�. Please accomplish this part
    perform_convolution();

    std::cout << "Convolution done." << std::endl << std::endl;

    std::cout << "Opening '" << outputFilename << "' for writing." << std::endl;

    output_file_id = fopen(outputFilename.c_str(), "w");
    fwrite(outdata, 1, DATASIZE, output_file_id);
    fclose(output_file_id);

    return 0;
}