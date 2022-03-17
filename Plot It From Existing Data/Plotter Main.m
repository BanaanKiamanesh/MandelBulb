clear;
close all;
clc;

%% Import File

DIM = 128;              % Resolution
data = importfile(128); % Import File

%% Plot the Point Cloud
pcshow(data)