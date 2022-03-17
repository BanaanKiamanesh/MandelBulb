clear;
close all;
clc;

%% Import File

DIM = 512;              % Resolution
data = importfile(DIM); % Import File

%% Plot the Point Cloud
pcshow(data)