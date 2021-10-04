#include <iostream>
#include <fstream>
#include <string>


#define DATASIZE 375000
#define WIDTH 750
#define HEIGHT 500
FILE *source_file_id, *output_file_id;
unsigned char data[DATASIZE], outdata[DATASIZE];
unsigned char transImage[DATASIZE * 2];
int x, y;
int filter[9] = {-1, -2, -3, -4, 0, 4, 3, 2, 1};

void convolute(){
    // std::cout << "Not implemented!" << std::endl;

    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            x = i;
            y = j;
            kernelGrid();
        }
    }
}

void kernelGrid(){

    int curPixel = (y * WIDTH) + x;
    int kernelConvolution = 0;
    std::cout<<"currently convoluting the pixel at ("<<x<<", "<<y<<")"<<::std::endl;
    if ((x == 0) || (x == (WIDTH - 1)) || (y == 0) || (y == (HEIGHT - 1))){
        kernelConvolution = data[curPixel];
    }else{

        // Matrix of values in filter
        int upL,upM,upR;
        int cenL,cenM,cenR;
        int lowL,lowM,lowR;


        //upper row of matrix
        int upRow = y - 1;
        upL = (upRow * WIDTH) + x - 1;
        upM = (upRow * WIDTH) + x;
        upR = (upRow * WIDTH) + x + 1;


        //central row of matrix
        cenL = curPixel - 1;
        cenM = curPixel;
        cenR = curPixel + 1;


        //lower row of matrix
        int lowRow = y + 1;
        lowL = (lowRow * WIDTH) + x - 1;
        lowM = (lowRow * WIDTH) + x;
        lowR = (lowRow * WIDTH) + x + 1;


        //adding each sector to kernal conv 
        kernelConvolution += data[upL] * filter[0];
        kernelConvolution += data[upM] * filter[1];
        kernelConvolution += data[upR] * filter[2];
        kernelConvolution += data[cenL] * filter[3];
        kernelConvolution += data[cenM] * filter[4];
        kernelConvolution += data[cenR] * filter[5];
        kernelConvolution += data[lowL] * filter[6];
        kernelConvolution += data[lowM] * filter[7];
        kernelConvolution += data[lowR] * filter[8];
    }

    
    std::cout<<"given ("<<data[curPixel]<<") value after using kernel conv ("<< kernelConvolution <<") "<<std::endl;

    int divValue = 0;
    for (size_t i = 0; i < sizeof(filter); i++)
    {
        divValue = abs(filter[i]);
    }
    
    outdata[curPixel] = kernelConvolution/divValue;
}

void createMargin(){

    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            x = i;
            y = j;
            changePixel(0);
        }
    }

    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            x = i;
            y = j;
            changePixel(1);
        }
    }

    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            x = i;
            y = j;
            changePixel(2);
        }
    }

    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            x = i;
            y = j;
            changePixel(3);
        }
    }
}

void changePixel(int channel){

    int curPixel = (y * WIDTH) + x;
    if (channel == 0){
        if ((x < 15) || (x > (WIDTH - 15)) || (y < 15) || (y < (HEIGHT - 15))){
            transImage[curPixel] = 30; 
        }else{
            transImage[curPixel] = 100;
        }
    }else{
        transImage[curPixel*(channel+1)]=data[curPixel];
    }

}

int main(int argc, char** argv)
{   
    std::string readFile = "unesco750-1.raw";
    std::string outputFile = "output.raw";
    std::cout<<"Attempting to open file"<<std::endl;
    source_file_id = fopen(readFile.c_str(), "r");
    fread(data, 1, DATASIZE, source_file_id);
    fclose(source_file_id);
    convolute();
    createMargin();
    std::cout<<"file opened writing"<<std::endl;
    output_file_id = fopen(outputFile.c_str(), "w");
    fwrite(transImage, 1, DATASIZE*2, output_file_id);
    fclose(output_file_id);
    return 0;
}
