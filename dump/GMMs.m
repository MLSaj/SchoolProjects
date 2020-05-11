                                           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% CSC C11 - Assignment 2 - Gaussian Mixture Models clustering
%
% In this function, you will implement Gaussian Mixture Models.
%  the mixture models can be initialized randomly, or with the
%  given initial centers.
%  Covariance matrices are initialized to identity.
%
% function [centers,covariances,labels]=GMMs(data,cent_init,k)
%
% Inputs: data - an array of input data points size n x d, with n 
%                input points (one per row), each of length d.
%         k - number of clusters
%         cent_init - either an empty array '[]', or an array of
%                     size k x d, with k initial cluster centers
%
% Outputs: centers - Final cluster centers
%          covariances - Covariance matrices for the GMM components,
%                        this will be an array of size
%                        d x d x k, with each 'layer' of size
%                        d x d corresponding to the covariance
%                        matrix of one of the Gaussians in the model.
%          mps - An array of size k x 1, with mixture proportions
%                giving the percent of data assigned to each
%                cluster. The sum of these has to be 1.
%          labels - An array of size n x 1, with labels indicating
%                   which cluster each input point belongs to.
%                   e.g. if data point i belongs to cluster j,
%                   then labels(i)=j
%
% Starter code: F. Estrada, Sep. 2017
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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


function [centers,covariances,mps,labels]=GMMs(data,cent_init,k)

% Initialize all the arrays we will need
centers=zeros(k,size(data,2));
labels=zeros(size(data,1),1);
mps=ones(k,1)/k;
covariances=zeros([size(data,2) size(data,2) k]);
for i=1:k
 covariances(:,:,i)=eye(size(data,2),size(data,2));
end;

if (isempty(cent_init))
  % Initial centers is an empty array, choose initial centers
  % randomly
  cent_init = datasample(data,k,'Replace',false); 
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % TO DO: Complete this part so that your code chooses k initial
  %        centers randomly. This comes down to picking random
  %        entries in your data array.
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
else
  if (size(cent_init,1)~=k | size(cent_init,2)~=size(data,2))
    fprintf(2,'Initial centers array has wrong dimensions.'\n');
    return;
  end;
end;
centers=cent_init;

convergence = false;
[n d] = size(data);
matrix = zeros([n k]);
lprime = zeros(size(data,1),1);
pdfswithmixed = zeros([n k]);
while convergence == false
    %E Step
        %Probability of point i existing to cluster j is
        %P(L=j|yi,theta)
        %Applying bayes rule this is equal to 
        %P(L=j|yi,theta) = P(L=j|theta)*P(y|theta,L=j)/(P(y|theta))
        %P(L=j|theta) = aj where aj is the mixed proportion
        %P(y|theta,L=j) = G(y,uj,varj) pdf of point y
        %P(y|theta) = Sum(G(y,uj,varj)*aj)
        d=k;
        
        for i =1:k
            x = data;
            %Get ith center
            u = centers(i,:);
            %subtract data by ith center (column vectros)
            x_minus_mu = x - u;
            %The distance is (x - mu)
            distances = x_minus_mu*inv(covariances(:,:,i)).*x_minus_mu;
            const = 1/sqrt(((2*pi)^d*det(covariances(:,:,i))));
            
            
            %firstpart = (x-u)'*inv(covariances(:,:,i));
            matrix(:,i) = const * exp((-1/2)*sum(distances,2));
            %matrix(:,i) = exp(log(const) + (-1/2)*sum(distances,2));   
        end
        
        [pdfswithmixed] = matrix.*mps';
        finalpdf = bsxfun(@rdivide, pdfswithmixed, sum(pdfswithmixed,2));
        x = data;
        [non,labels] = max(finalpdf,[],2);
        %checkfor convergence
        convergence = isequal(lprime,labels);
        if(convergence == true)
            break;
        end
        lprime = labels;
        %Mstep
        for j=1:d
            u = centers(j,:);
            x_minus_mu = x - u;
            mps(j) = sum(finalpdf(:,j))/size(data,1);
            centers(j,:) = sum(finalpdf(:,j)'*data,1)/sum(finalpdf(:,j));
            new_sigma = (finalpdf(:,j).*x_minus_mu)'*(x_minus_mu)/sum(finalpdf(:,j));
            covariances(:,:,j) = new_sigma;
        end
    
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% TO DO: Complete the function by implementing the E-M algorithm for
%  estimating the parameters of a Gaussian Mixture Model
% 
%        As a reminder, this is a loop that:
%          * Assigns data points to the cluster that gives it maximum 
%            likelihood
%          * Updates the cluster centers, covariances, and mixture 
%            proportions
%          * Update the labels array to contain the index of the
%            cluster center each point is assigned to
%        Loop ends when the labels do not change from one iteration
%         to the next. 
%
%  DO NOT compute ownership probabilities for data points using
%   a for loop over data points. Doing so will cause you to wait
%   forever for this thing to converge. Your TA certainly won't
%   wait that long.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

