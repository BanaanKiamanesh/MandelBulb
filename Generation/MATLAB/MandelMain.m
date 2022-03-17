clear;
close all;
clc;

%% Parameter Declaration
DIM = 128;
maxiterations = 20;
n = 8;

mandelbulb = [];

%% Setup

for i = 1:DIM
    for j = 1:DIM

        edge = false;
        lastIteration = 0;

        for k = 1:DIM

            x = i/DIM * 2 - 1;        % Map i into [-1, 1]
            y = j/DIM * 2 - 1;        % Map j into [-1, 1]
            z = k/DIM * 2 - 1;        % Map k into [-1, 1]

            zeta.x = 0;
            zeta.y = 0;
            zeta.z = 0;

            iteration = 0;

            while 1
                c.r = sqrt(zeta.x * zeta.x + zeta.y * zeta.y + zeta.z * zeta.z);
                c.theta = atan2(sqrt(zeta.x*zeta.x + zeta.y * zeta.y), zeta.z);
                c.phi = atan2(zeta.y, zeta.x);

                newx = c.r^n * sin(c.theta*n) * cos(c.phi*n);
                newy = c.r^n * sin(c.theta*n) * sin(c.phi*n);
                newz = c.r^n * cos(c.theta*n);

                zeta.x = newx + x;
                zeta.y = newy + y;
                zeta.z = newz + z;

                iteration = iteration + 1;

                if (c.r > 2)

                    lastIteration = iteration;

                    if edge
                        edge = false;
                    end

                    break;
                end

                if iteration > maxiterations
                    if ~edge
                        edge = true;
                        mandelbulb = cat(1, mandelbulb, [x, y, z]);
                    end

                    break;
                end
            end
        end
    end
end


%% Plot the Point Cloud
pcshow(mandelbulb)

% Save the Matrix
writematrix(mandelbulb,['MandelData_' num2str(DIM) '.csv'],'Delimiter',',')
clear