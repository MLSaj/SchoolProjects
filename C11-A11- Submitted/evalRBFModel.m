% CSC C11 - Machine Learning, Fall 2017, Assignment 1, 
% F. Estrada, festrada@utsc.utoronto.ca
%
% A 2D - Radial Basis Function
% 
% [z]=evalRBFModel(w,P,C,sigma)
%
% Evaluates the trained RBF model with weights w at
% the specified points.
%
% w - weights for the RBFs in the model as estimated by
%     TrainRBFRegression.m
%
% P - a 2-row array containing the coordinates of the points
%     where we want the model to be evaluated, i.e.
%
%     P=[x_1   x_2    ....    x_n
%        y_1   y_2    ....    y_n]
%
% C - RBF center locations, i.e.
%
%     C=[cx_1  cx_2   ....    cx_n
%        cy_1  cy_2   ....    cy_n]
%
% sigma - width of the RBFs
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% TO DO: Complete this function so that it evaluates the trained
%        RBF model on the given input points
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% COMPLETE THIS TEXT BOX:
%
% 1) Student Name:Sajeed Bakht		
% 2) Student Name: Sankalp Sharma	
%
% 1) Student number:1001527975
% 2) Student number:1002352465
% 
% 1) UtorID bakhtsye
% 2) UtorID sharm697
% 
% We hereby certify that the work contained here is our own
%
% ____________________             _____________________
% (sign with your name)            (sign with your name)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% COMPLETE THIS TEXT BOX:
%
% Code written by:
%
% 1) Student Name:		Student number:			UtorID:
% 2) Student Name:		Student number:			UtorID:
%
% We hereby certify that the work contained here is our own
%
%
% ____________________             _____________________
% (sign with your name)            (sign with your name)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [z]=evalRBFModel(w,P,C,sigma)
    [m,k] = size(C);
    %k = length(C);
    %n = length(P);
    [l,n] = size(P);
    matrixofrbfval = zeros([n k]);
    for i=1:n
        %Pcolumn C(:,i),
        vectorpart = zeros(1,k);
        for(j=1:k) 
            %P Column P(:,j)
            rbfval = rbf2d(P(:,i), C(:,j),sigma);
            vectorpart(j) = rbfval;


        end
        %fills in matrix
        matrixofrbfval(i,:) = vectorpart;
    end
    biasterm = ones(n,1);
    Bmatrix = [matrixofrbfval, biasterm];
    [z] = (Bmatrix*w);
   %[z] = Bmatrix*w
        

  % for loop through z
  % add w * rbf2d(p,c,sigma) for each point point center and sigma
  %
  