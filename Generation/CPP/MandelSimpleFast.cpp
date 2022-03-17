#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Init..." << std::endl;

    // Params
    const int DIM = 512;
    const int maxiterations = 20;
    const int n = 8;

    // Create File and Write the Header
    std::cout << "\nCreating the File..." << std::endl;
    std::ofstream out("MandelData.csv");
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
                float x = (float)i / DIM * 2 - 1;
                float y = (float)j / DIM * 2 - 1;
                float z = (float)k / DIM * 2 - 1;

                float zeta_x = 0;
                float zeta_y = 0;
                float zeta_z = 0;

                int iteration = 0;
                while (true)
                {
                    float c_r = sqrt(zeta_x * zeta_x + zeta_y * zeta_y + zeta_z * zeta_z);
                    float c_theta = atan2(sqrt(zeta_x * zeta_x + zeta_y * zeta_y), zeta_z);
                    float c_phi = atan2(zeta_y, zeta_x);

                    float newx = pow(c_r, n) * sin(c_theta * n) * cos(c_phi * n);
                    float newy = pow(c_r, n) * sin(c_theta * n) * sin(c_phi * n);
                    float newz = pow(c_r, n) * cos(c_theta * n);
                    zeta_x = newx + x;
                    zeta_y = newy + y;
                    zeta_z = newz + z;
                    iteration++;

                    if (c_r > 2)
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