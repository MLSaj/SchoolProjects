%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CSC C11 - Assignment 3 - Dimensionality reduction by PCA
%
% In this function you will apply PCA to an input dataset to
% return a low-dimensional representation for the input data.
%
% Inputs:
% 
% input_data    -   Input dataset, one sample PER ROW
% k             -   Number of dimensions for the low-dimensional data
%
% Return values:
%
% LodDim_data   -   The low-dimensional representation of the dataset
%                   one sample per row
% V             -   The matrix with the PCA directions (one per column)
% mu            -   The mean of the input data (needed for reconstruction)
% 
% F.J.E. Nov, 2017
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [LowDim_data,V,mu]=datasetPCA(input_data, k);
    %Step 2 from tutorial
    %gets means and subtracts it from data
    mu = mean(input_data);
    mean_input_data = bsxfun(@minus,input_data,mu);
    %Step 3 
    %Calculate covariance matrix
    cov_input_data = eig(input_data);
    %Step 4
    %Calculate eigenvectors and eigenvalues of the covariance matrix
    %sort them by greatest algebraic value 'la'
    [eigvectors,eigvalues] = eigs(cov_input_data,k,'la');
    %Step 5
    %Deriving the new data set
    %FinalData = RowFeatureVector * RowDataAdjust
    %Where RowFeatureVector is column transpose so eigvectors in rows
    %RowDataAdjust is mean adjusted data transposesd
    V = eigvalues'
    row_data_adjust = mean_input_data';
    row_feature_vector = eigvectors';
    LowDim_data = row_feature_vector * row_data_adjust
    LowDim_data = LowDim_data'


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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% TO DO: Complete the code below to find the PCA directions.
%        
%        Note: Use the eigs() function for computing the 
%              eigenvalues and eigenvectors.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

