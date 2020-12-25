

#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"
#include "immintrin.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter *readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
    }

    //
    // Convert to C++ strings to simplify manipulation
    //
    string filtername = argv[1];

    //
    // remove any ".filter" in the filtername
    //
    string filterOutputName = filtername;
    string::size_type loc = filterOutputName.find(".filter");
    if (loc != string::npos)
    {
        //
        // Remove the ".filter" name, which should occur on all the provided filters
        //
        filterOutputName = filtername.substr(0, loc);
    }

    Filter *filter = readFilter(filtername);

    double sum = 0.0;
    int samples = 0;

    for (int inNum = 2; inNum < argc; inNum++)
    {
        string inputFilename = argv[inNum];
        string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
        struct cs1300bmp *input = new struct cs1300bmp;
        struct cs1300bmp *output = new struct cs1300bmp;
        int ok = cs1300bmp_readfile((char *)inputFilename.c_str(), input);

        if (ok)
        {
            double sample = applyFilter(filter, input, output);
            sum += sample;
            samples++;
            cs1300bmp_writefile((char *)outputFilename.c_str(), output);
        }
        delete input;
        delete output;
    }
    fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);
}

class Filter *
readFilter(string filename)
{
    ifstream input(filename.c_str());

    if (!input.bad())
    {
        int size = 0;
        input >> size;
        Filter *filter = new Filter(size);
        int div;
        input >> div;
        filter->setDivisor(div);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                int value;
                input >> value;
                filter->set(i, j, value);
            }
        }
        return filter;
    }
    else
    {
        cerr << "Bad input in readFilter:" << filename << endl;
        exit(-1);
    }
}

double applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{
    long long cycStart, cycStop;

    cycStart = rdtscll();
    int col, row, i, j, mrow, mcol, rval, gval, bval;

    output->width = input->width;
    output->height = input->height;
    int height = (input->height) - 1;
    int width = (input->width) - 1;
    
    char divisor = filter->getDivisor();
    int *data = filter->data;

    if (divisor == 1)
    {
        #pragma omp parallel for
        for (row = 1; row < height; row++)
        {
            for (col = 1; col < width; col++)
            {
                mrow = row - 1;
                mcol = col - 1;

                rval = gval = bval = 0;

                for (j = 0; j < 3; j++)
                {
                    for (i = 0; i < 3; i++)
                    {
                        //output->color[row][col].R = output->color[row][col].R + (input->color[row + i - 1][col + j - 1].R * filter->get(i, j));
                        rval += input->color[mrow + i][mcol + j].R * data[i * 3 + j];
                        gval += input->color[mrow + i][mcol + j].G * data[i * 3 + j];
                        bval += input->color[mrow + i][mcol + j].B * data[i * 3 + j];
                    }
                }
                rval = (rval < 0) ? 0 : rval;
                gval = (gval < 0) ? 0 : gval;
                bval = (bval < 0) ? 0 : bval;

                rval = (rval > 255) ? 255 : rval;
                gval = (gval > 255) ? 255 : gval;
                bval = (bval > 255) ? 255 : bval;
                
                output->color[row][col].R = rval;
                output->color[row][col].G = gval;
                output->color[row][col].B = bval;
            }
        }
    }

    if (divisor != 1)
    {
        #pragma omp parallel for
        for (row = 1; row < height; row++)
        {
            for (col = 1; col < width; col++)
            {
                mrow = row - 1;
                mcol = col - 1;

                rval = gval = bval = 0;

                for (j = 0; j < 3; j++)
                {
                    for (i = 0; i < 3; i++)
                    {
                        rval += input->color[mrow + i][mcol + j].R * data[i * 3 + j];
                        gval += input->color[mrow + i][mcol + j].G * data[i * 3 + j];
                        bval += input->color[mrow + i][mcol + j].B * data[i * 3 + j];
                    }
                }
                rval /= divisor;
                gval /= divisor;
                bval /= divisor;

                output->color[row][col].R = rval;
                output->color[row][col].G = gval;
                output->color[row][col].B = bval;
            }
        }
    }

    cycStop = rdtscll();
    double diff = cycStop - cycStart;
    double diffPerPixel = diff / (output->width * output->height);
    fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
            diff, diff / (output->width * output->height));
    return diffPerPixel;
}
