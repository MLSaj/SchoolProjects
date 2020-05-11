%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CSC C11 - Assignment 3 - Classification by Gaussian Class Conditionals
%
% This function uses a trained GCC model to classify an input dataset
%
% Inputs:
%
% input_data   -  The training data set  (one input sample per row)
% centers      -  Centers of the Gaussians in the GCC model
% covs         -  Covariances for the Gaussians in the GCC model
% ais          -  Mixture proportions
%
% Returns:
%
% labels       - Output labels for input data samples. Each entry is a
%                value in [1,K] for a GCC model with K components.
%
% F.J.E. Nov, 2017
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [labels]=GCC_Classify(input_data,centers,covs,ais);
%Do E step from GMM
    for i =1:K
        %Get ith center
        u = centers(i,:);
        %subtract data by ith center (column vectros)
        x_minus_mu = input_data - u;
        %The distance is (x - mu)
        distances = x_minus_mu*inv(covs(:,:,i)).*x_minus_mu;
        const = 1/sqrt(((2*pi)^d*det(covs(:,:,i))));
        %firstpart = (x-u)'*inv(covariances(:,:,i));
        matrix(:,i) = const * exp((-1/2)*sum(distances,2));
        %matrix(:,i) = exp(log(const) + (-1/2)*sum(distances,2));
    end
    [pdfswithmixed] = matrix.*ais';
    finalpdf = bsxfun(@rdivide, pdfswithmixed, sum(pdfswithmixed,2));
    [non,labels] = max(finalpdf,[],2);
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
% TO DO: Complete the function to classify the input dataset using
%        the model provided. The classification rule should be
%        familiar to you from your GMMs
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
