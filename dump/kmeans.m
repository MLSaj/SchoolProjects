%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% CSC C11 - Assignment 2 - K-means clustering
%
% This function implements K-means clustering for a set of input
%  vectors, and an *initial* set of cluster centers. If the initial
%  set is empty, it initializes the centers and proceeds to do
%  the clustering.
%
% function [centers,labels]=kmeans(data,cent_init,k)
%
% Example calls (assuming data contains vectors of length 3 in each row)
%
% [centers,labels]=kmeans(data,[],5);	% Choose initial centers
%                                       % for 5 clusters
%
% [centers,labels]=kmeans(data,[1 2 3; 4 5 6],2);  % use initial centers
%                                                  % [1 2 3] and [4 5 6]
% 
%
% Inputs: data - an array of input data points size n x d, with n 
%                input points (one per row), each of length d.
%         k - number of clusters
%         cent_init - either an empty array '[]', or an array of
%                     size k x d, with k initial cluster centers
%
% Outputs: centers - Final cluster centers
%          labels - An array of size n x 1, with labels indicating
%                   which cluster each input point belongs to.
%                   e.g. if data point i belongs to cluster j,
%                   then labels(i)=j
%
% Starter code: F. Estrada, Sep. 2017
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [centers,labels]=kmeans(data,cent_init,k)

centers=zeros(k,size(data,2));
labels=zeros(size(data,1),1);

if (isempty(cent_init))
  % Initial centers is an empty array, choose initial centers
  % randomly
  cent_init = datasample(data,k,'Replace',false)   
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
end
centers=cent_init;

  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% TO DO: Complete the function by implementing the k-means algorithm
%        below.P = [1 2
% 
%        As a reminder, this is a loop that:
%          * Assigns data points to the closest cluster center
%          * Re-computes cluster centers based on the data points
%            assigned to them.
%          * Update the labels array to contain the index of the
%            cluster center each point is assigned to
%        Loop ends when the labels do not change from one iteration
%         to the next. 
%
%  DO NOT compute distances from data points to cluster centers
%   with a for loop over data points. Doing so will cause you to wait
%   forever for this thing to converge. Your TA certainly won't%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   wait that long.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[k,d] = size(centers);
[n,d] = size(data);
convergence = false;
lprime=zeros(size(data,1),1);
convergence = false;
  while convergence == false
      Distances = sqrt( bsxfun(@plus,sum(centers.^2,2),sum(data.^2,2)') - 2*(centers*data') )';
      
      [non,labels] = min(Distances,[],2);
      %LMatrix
      %LPrime
      convergence = isequal(lprime,labels);
      if(convergence == true)
          break;
      end
      lprime = labels;
      for i=1:k
          points_in_center = find(labels == i);
          [total_points,row] = size(points_in_center);
          if(total_points ~= 1)
          total_center = sum(data(points_in_center,:))
          new_center = total_center/total_points;
          centers(i:i,:) = new_center;
          else
          centers(i:i,:) = data(points_in_center,:);
          end
      end
  end
  
  
  
end


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

