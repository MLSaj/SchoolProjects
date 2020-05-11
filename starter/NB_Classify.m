%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CSC C11 - Assignment 3 - Naive Bayes classification
%
% This function classifies the input dataset using a trained NB
% classifier
%
% Inputs:
% 
% input_data       -  Input data set, one sample PER ROW
% NB_probs         -  A kxD array whose rows are the probabilities
%                     for input features being = 1 for each class
% NB_ais           -  A kx1 array with p(L=i)
% 
% Return values:
%
% labels           - Labels for input samples in [1,K]
%
% F.J.E. Nov, 2017
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [labels]=NB_Classify(input_data, NB_probs, NB_ais)
%find which columns it doesn't equal 0
[examples, col] = size(input_data)
[classes,column] = size(NB_ais)
feature_vector_belong =size(examples,classes)
labels = zeros(1, examples)
for i=1:examples
    feature_vector = input_data(i,:);
    for j=1:classes
        NB_probsClass = (NB_probs(j,:));
        %express in terms of log
        NB_probsNonActive = (1 - NB_probs(j,:));
        [active_features] = find(feature_vector == 1);
        [nonActive_features] = find(feature_vector == 0);
        prob = (prod(NB_probsClass(active_feautures)) + prod(NB_probsNonActive(nonActive_features)));
        +log(NB_ais(j));
        feature_vector_belong(j) = prob;
    end
    class = max(feature_vector_belong);
    labels(1,i) = class;
end
    
    %loop through each row
    
    

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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% TO DO: Complete this function to perform NB classification
%
%        NOTE: You will be multiplying lots of tiny numbers. That
%              will quickly run you into trouble. You should do
%              everything in the log domain instead.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

