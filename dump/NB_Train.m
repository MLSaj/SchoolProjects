%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CSC C11 - Assignment 3 - Naive Bayes classifier training
%
% This function computes the parameters of a Naive Bayes classifier 
% for the given training dataset
%
% Inputs:
% 
% training_data    -  The training data set, one sample PER ROW
% training_labels  -  Labels for the training dataset
% K                -  Number of classes
% 
% Return values:
%
% NB_probs         -  A kxD array whose rows are the probabilities
%                     for input features being = 1 for each class
% NB_ais           -  A kx1 array with p(L=i)
%
% F.J.E. Nov, 2017
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [NB_probs, NB_ais]=NB_Train(training_data, training_labels, K)
%NB_ai a kX1 array with(L=i)
%count how many occurrences of class k was in training_labels and then divide it by
%the total occurrences 
%


%First binarize the data
training_data(training_data>0) = 1;
%Training labels start at 0, so lets adjust it to 1.
training_labels = training_labels + 1;
[points_in_trainLabels, col] = size(training_data);
NB_probs = zeros(K,col);
NB_ais = zeros(K,1);
for i=1:K
    [points_in_classK] = find(training_labels == i);
    [brah, size_of_classK] = size(points_in_classK);
    NB_ais(i) = size_of_classK/points_in_trainLabels;
    if NB_ais(i) == 0
        NB_ais = 1e-9;
    end
    classKExamples = training_data(points_in_classK,:);
    for j=1:col
        colExamplesK = classKExamples(:,j);
        [feature1] = find(colExamplesK == 1);
        [size_feature1, blah] = size(feature1);
        if size_feature1 > 0
            value = size_feature1/size_of_classK;
            NB_probs(i,j) = value;
        else
            NB_probs(i,j) = 1e-9;
        end
    end
end
end



    
%NB_probs
%P(F_1:D | C=j)
%P(F_i = 1 | C=j) 
%Training data 
% [1 0 
%  0 1
%  1 1
%  0 0]
%training_labels
% [1, 2 ,3, 1]
%P(F_i = 1 | C = j)
%Class 1 
%P(F_1 = 1 | C= 1) = 1/2 
%P(F_2 = 1 | C = 1) = 0

%Class 2
%P(F_1 = 1 | C =2) = 0
%P(F_2 = 1| C = 2) = 1

%Class 3
%P(F_1 = 1 | C = 3) = 1
%P(F_2 = 1 | C = 3) = 1 
%Our NB_probs matrix is 
%[0.5 0
% 0  0.5
% 0.5 0.5]
%Loop Through all class
%for each
%        NOTE: For this classifier you will assume features are
%              binary - that is, a word is either present in the
%              document or it is not. The training dataset provided
%              is *not* binary, you have to binarize your  class j
    %extact only the examples of class j
    %Loop through each feauture column i that exist to class
    %add up all the 1's divided by total amount 










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
% TO DO: Complete this function to estimate the parameters of the NB
%        classifier.
%
%        NOTE:
%                                                                                                                                                                              
%             
%              Second note: You should *not* allow any probabilities
%                to become zero, even if no document for a given
%                class contains a particular word, we should not 
%                assume this word is *never* found in documents
%                for the class. Therefore, once you have your
%                probability vectors for each class, replace 
%                any zeros with a tiny value such as 1e-9
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

