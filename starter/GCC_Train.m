%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CSC C11 - Assignment 3 - Classification by Gaussian Class Conditionals
%
% In this function, you will implement the code that trains the GCC model
% for the input dataset. 
%
% Inputs:
%
% train_data   -  The training data set  (one input sample per row)
% train_labels -  Labels for the training data set
% K            -  Number of components in the GCC model
%
% Returns:
%
% centers      - Each row is the center of a Gaussian in the GCC model
% covs         - A NxNxK matrix with K, NxN covariance matrices
% ais          - Mixture proportions
%
% F.J.E. Nov, 2017
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [centers,covs,ais]=GCC_train(train_data,train_labels,K);

%Take all training data that belongs to class j
%and estimate they're mean and variance
[examples, col] = size(train_data)
centers = zeros(K,col);
covs = zeros(examples,examples, K);
for i=1:K
    [points_in_classK] = find(training_labels == i);
    centers(i,:) = mean(points_in_classK);
    covs(:,:,i) = cov(points_in_classK);
end
%for label 
%for centers take all points in training_data belong to label k
%and average them for center

%for covariance take all points in training_data 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% COMPLETE THIS TEXT BOX:
%
% 1) Student Name:		
% 2) Student Name:		
%
% 1) Student number:
% 2) Student number:
% 
% 1) UtorID
% 2) UtorID
% 
% We hereby certify that the work contained here is our own
%
% ____________________             _____________________
% (sign with your name)            (sign with your name)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% TO DO: Complete the function to learn the parameters of the model
%        this should be fairly similar to your GMMs from A2!
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
