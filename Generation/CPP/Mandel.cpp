#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

// Vector Struct Def
struct vector
{
    float x;
    float y;
    float z;
};

//////// Class Def
class MandelPoint
{
public:
    vector v;
    float i;

    MandelPoint(vector v, float i)
    {
        this->v = v;
        this->i = i;
    }
};

class Spherical
{
public:
    float r, theta, phi;
    Spherical(float r, float theta, float phi)
    {
        this->r = r;
        this->theta = theta;
        this->phi = phi;
    }
};

//////// Func Def
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Spherical spherical(float x, float y, float z)
{
    float r = sqrt(x * x + y * y + z * z);
    float theta = atan2(sqrt(x * x + y * y), z);
    float phi = atan2(y, x);

    return Spherical(r, theta, phi);
}

// ArgParse Funcs
char *getCmdOption(char **begin, char **end, const std::string &option)
{
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[])
{
    std::cout << "Init..." << std::endl;

    // Params
    int DIM = 128;
    const int maxiterations = 20;
    int n = 8;

    // ArgParse
    if (cmdOptionExists(argv, argv + argc, "-d")) // if -d is passed then init DIM
    {
        DIM = atoi(getCmdOption(argv, argv + argc, "-d"));
    }

    if (cmdOptionExists(argv, argv + argc, "-n")) // if -n is passed then init n
    {
        n = atoi(getCmdOption(argv, argv + argc, "-n"));
    }

    // Create File and Write the Header
    std::cout << "\nCreating the File..." << std::endl;
    // make the file name with the dim in it
    std::string fileName = "MandelData_" + std::to_string(DIM) + ".csv";
    std::ofstream out(fileName);
    out << "x"
        << ","
        << "y"
        << ","
        << "z"
        << "\n";

    std::cout << "Mandelbrot Set Main Loop Running..." << std::endl;
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            bool edge = false;
            int lastIteration = 0;

            for (int k = 0; k < DIM; k++)
            {
                float x = map(i, 0, DIM, -1, 1);
                float y = map(j, 0, DIM, -1, 1);
                float z = map(k, 0, DIM, -1, 1);

                vector zeta = {0, 0, 0};

                int iteration = 0;
                while (true)
                {
                    Spherical c = spherical(zeta.x, zeta.y, zeta.z);
                    float newx = pow(c.r, n) * sin(c.theta * n) * cos(c.phi * n);
                    float newy = pow(c.r, n) * sin(c.theta * n) * sin(c.phi * n);
                    float newz = pow(c.r, n) * cos(c.theta * n);
                    zeta.x = newx + x;
                    zeta.y = newy + y;
                    zeta.z = newz + z;
                    iteration++;

                    if (c.r > 2)
                    {
                        lastIteration = iteration;
                        if (edge)
                        {
                            edge = false;
                        }
                        break;
                    }

                    if (iteration > maxiterations)
                    {
                        if (!edge)
                        {
                            edge = true;
                            out << x << "," << y << "," << z << "\n";
                        }
                        break;
                    }
                }
            }
        }
    }

    out.close();
    std::cout << "Done!" << std::endl;

    return 0;
}