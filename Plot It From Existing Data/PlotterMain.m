clear;
close all;
clc;

%% Import File

DIM = 256;              % Resolution
data = importfile(DIM); % Import File

%% Plot the Point Cloud
pcshow(data)
axis off