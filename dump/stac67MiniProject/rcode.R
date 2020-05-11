setwd('/Users/sajeedbakht/Desktop/stac67MiniProject')
#Removing highly correlated variables
mydata <- read.csv("data.csv", header = TRUE)
head(mydata)
corr <- cor(mydata)[2:200,2:200]
high_corr <- c();
t <- colnames(corr)
for(row in 1:nrow(corr)) {
  for(col in 1:ncol(corr)) {
    if((abs(corr[row,col]) > 0.7) && (col != row) && !(row %in% high_corr) && !(col %in% high_corr)){
    print((colnames(corr)[col]))
    a <- (colnames(corr)[col])
    #print(paste(colnames(corr)[col], "and", rownames(corr)[row], 
            #"have a correlation of", corr[row,col]))
    high_corr <- append(high_corr, col)
    
    
    }
  }
}
print(high_corr)
print(length(high_corr))
high_len = length(high_corr)
reduced_data <- mydata[2:200]
t <- colnames(reduced_data)
high_corr_names = c()
for(i in high_corr){
  print(i)
  print(t[i])
  high_corr_names <- append(high_corr_names, t[i])
}

r_data <- mydata[ , !(names(mydata) %in% high_corr_names)]
head(r_data)


#StepWise Model selection procedure
full <- lm(y ~ ., data = r_data)
null <- lm(y ~ 1, data = r_data)
finalfit <- step(null, scope=list(lower=null, upper=full), direction="forward")

alsofinalfit <- lm(y ~ x87+ x11 + x185+ x62 + x54 + x187 + x96+ x51 + x184, data = r_data)
 

#Part C
#We use extra sum of squares princepal comparing an Ftest with each F
alpha <- 0.01
FTAB <- qf(1 - alpha, 1, 120)

x184reduced <- lm(y ~ x87+ x11 + x185+ x62 + x54 + x187 + x96+ x51, data = r_data)
anova(x184reduced,finalfit)
#Remove184 FTAB > F*

x51reduced <- lm(y ~ x87+ x11 + x185+ x62 + x54 + x187 + x96 + x184, data = r_data)
anova(x51reduced,finalfit)
#Keep x51 F* > FTAB


x96reduced <- lm(y ~ x87+ x11 + x185+ x62 + x54 + x187 + x51 + x184, data = r_data)
anova(x96reduced,finalfit)
#Remove x96


x187reduced <- lm(y ~ x87+ x11 + x185+ x62 + x54 + x96+ x51 + x184, data = r_data)
anova(x187reduced,finalfit)
#Remove x187


x54reduced <- lm(y ~ x87+ x11 + x185+ x62 + x187 + x96+ x51 + x184, data = r_data)
anova(x54reduced,finalfit)
#Remove x54

x62reduced <- lm(y ~ x87+ x11 + x185+ x54 + x187 + x96+ x51 + x184, data = r_data)
anova(x62reduced,finalfit)
#Remove x62

x185reduced <- lm(y ~ x87+ x11 + x62 + x54 + x187 + x96+ x51 + x184, data = r_data)
anova(x185reduced,finalfit)
#Remove x185

x11reduced <- lm(y ~ x87+ x185+ x62 + x54 + x187 + x96+ x51 + x184, data = r_data)
anova(x11reduced,finalfit)
#Keep x11

x87reduced <- lm(y ~ x11+ x185+ x62 + x54 + x187 + x96+ x51 + x184, data = r_data)
anova(x11reduced,finalfit)
#Keepx87



## R function to perform K-fold cross-validation ##
CV.K.FOLD <- function(data, form, K = 10){
  
  n <- dim(data)[[1]] ## number of observations ##
  Y <- data$y  ## response variable ##
  if(K > n) stop("K should be <= n, number of observations")
  f <- ceiling(n/K)
  s <- sample(rep(1:K, f), n) ## validation folds ##
  ms <- max(s)
  MSPE <- 0 ## initiation of the mean squared prediction error ##
  coef <- NULL
  MSE <- NULL
  AY <- PY <- NULL
  
  for(v in 1:ms){
    j.in <- c(1:n)[(s != v)]
    j.out <- c(1:n)[(s == v)]
    
    data.train <- data[j.in,]
    data.test <- data[j.out,]
    data.train <- as.data.frame(data.train)
    data.test <- as.data.frame(data.test)
    
    fit.train <- lm(form, data = data.train) ## fitting model using training data ##
    coef <- cbind(coef, coefficients(fit.train))
    MSE <- c(MSE, summary(fit.train)$sigma^2)
    pred.test <- predict(fit.train, newdata = data.test) ## prediction for the validated data ##
    cat("Validation Set =", v, "\n\n\n") ## validation set number ##
    cat("Fitted Model Using Training Data \n\n\n")
    print(summary(fit.train)) ## fitted model to the training data ##
    print(anova(fit.train)) ## anova table for the fitted model to the training data ##
    
    cat("Observation Numbers =", c(1:n)[j.out], "\n\n\n") ## observation numbers in the validation set ##
    cat("Actual Observations =", Y[j.out], "\n\n\n") ## observed response in the validation set ##
    cat("Predicted Observations =", pred.test, "\n\n\n") ## predicted response in the validation set ##
    MSPE <- MSPE + sum((Y[j.out] - pred.test)^2)
    AY <- c(AY, Y[j.out])
    PY <- c(PY, pred.test)
  }
  
  MSPE <- MSPE/n ## overall mean squared prediction error ##
  cat("Overall Mean Squared Prediction Error", MSPE, "\n\n") 
  coef <- rbind(coef, MSE)
  colnames(coef) <- paste("Fold", 1:K, sep = ":")
  cat("Estimated Coefficients \n\n")
  print(coef) 
  plot(AY, PY, xlab = "Observed Response", ylab = "Predicted Response", xlim = range(c(AY, PY)), ylim = range(c(AY, PY)), main = "")
}

set.seed(1)
form <- as.formula(y ~ x11 + x87 + x51)
CV.K.FOLD(data = r_data, form, K = 10)

plot(x=r_data$x11, y=r_data$y, xlab = "Predictor Variable x11", ylab ="Response Variable")

plot(x=r_data$x87, y=r_data$y, xlab = "Predictor Variable x87", ylab ="Response Variable")
plot(x=r_data$x51, y=r_data$y, xlab = "Predictor Variable x51", ylab ="Response Variable")


finalcolnames = c("x11","x87","x51");
finaldata <- r_data[ , (names(r_data) %in% finalcolnames)]
fit <- lm(y~x11 + x87 + x51, data = r_data)
yhati <- fitted(fit) #predicted values
ei <- residuals(fit) # residuals
X <-as.matrix(cbind(1,finaldata))
#Influential y observations
hat_mat <- X %*% solve(t(X) %*% X) %*% t(X) ## hat matrix
hii <- diag(hat_mat)

MSE <- (summary(fit)$sigma)^2 ## mean squared error

s2ei <- MSE * (1 - hii) # estimated variance of the ith residual

I <- matrix(0, nrow = dim(hat_mat)[[1]], ncol = dim(hat_mat)[[1]])
diag(I) <- 1 ## I: identity matrix 
s2e <- MSE * (I - hat_mat) # estimated variance-covariance matrix of the residuals 

ri <- ei/sqrt(s2ei) #studentized residuals
n <- dim(finaldata)[[1]]
p <- 4 ## number of regression coefficients parameters
SSE <- sum(ei^2) ##error sum of squares
ti <- ei * sqrt((n - p - 1)/(SSE * (1 - hii) - ei^2)) # studentized deleted residuals
alpha <- 0.05

BCV <- qt(1 - alpha/(2*n), n - p - 1) ## Bonferroni Critical Value 

absti <- abs(ti)

index_of_outlier <- c(1:n)[absti >= BCV]

## Use of Hat Matrix to find outlying cases with regard to X values 

hii <- diag(hat_mat) ## diagonal elements of that hat matrix
hsum <- sum(hii)
hmean <- hsum/n
cutoff <- 2 * hmean
index_of_outlier <- c(1:n)[hii > cutoff]


## Idenfifying Influential Cases - DFFITS, Cook's Distance, and DFBETAS ##

## Computing DFFITS_i ##

dffits <- ti * sqrt(hii/(1 - hii))

adffits <- abs(dffits)
cutoff <- 2*sqrt(p/n) #200 is a large dataset
index_of_infl <- c(1:n)[adffits > cutoff]


## Cook's distance ##

Di <- ((ei^2)/ (p * MSE)) * (hii/(1 - hii)^2)
PERF <- pf(Di, df1 = p, df2 = (n - p))
cbind(Di, PERF)
index_of_infl <- c(1:n)[PERF >= 0.50]


## DFBETAS ##


## R function to compute DFBETAS ##

DFBETAS <- function(data, form){
  ## we assume that the response variable is in the first column of data ##
  n <- dim(data)[[1]] ## number of observations ##
  X <- as.matrix(cbind(1, data[, - 1])) ## X matrix
  invXX <- solve(t(X) %*% X) ## inverse of t(X)X ##
  dfbetas <- NULL
  for(i in 1:n){
    j.in <- c(1:n)[(c(1:n) != i)]
    data.train <- data[j.in,]
    data.train <- as.data.frame(data.train)
    
    fit.all <- lm(form, data = data) ## fitting model using all of the observations 
    coef.all <- coefficients(fit.all) # coefficients of the model that uses all of the observations
    
    fit.train <- lm(form, data = data.train) ## fitting model using training data ##
    coef.train <- coefficients(fit.train) # coefficients of the model that uses all of the observations
    
    MSE_i <- summary(fit.train)$sigma^2
    c_kk <- diag(invXX)
    
    dfbetas_i <- (coef.all - coef.train)/sqrt(MSE_i * c_kk)
    dfbetas <- rbind(dfbetas, dfbetas_i)
  }
  rownames(dfbetas) <- c(1:n)
  print(dfbetas)
}

finalcolnamesY = c("y", "x11","x87","x51");
finaldataY <- r_data[ , (names(r_data) %in% finalcolnamesY)]
form <- as.formula(y ~ x11 +x87 + x51)
DFBETAS(data = finaldataY, form)

#Correlation
## Multicollinearity: Variance Inflation Factor ##

VIF <- function(data){
  ## first column of "data" contains the response variable ##
  ## the columns starting from second to the last contain the predictor variables ##
  p <- dim(data)[[2]]
  colnames(data) <- c("Y", paste("X", c(1:(p - 1)), sep = ""))
  vif <- NULL
  for(i in 1:(p - 1)){
    form <- paste(paste("X", i, sep = ""), paste(paste("X", c(1:(p - 1))[-i], sep = ""), collapse=" + "), sep = " ~ ")
    form <- as.formula(form)
    fit.reg <- lm(form, data = data)
    R2 <- summary(fit.reg)$r.squared
    vifk <- 1/(1 - R2)
    vif <- c(vif, vifk)
  }
  cat("Variance Inflation Factors = ", vif, "\n\n")
  maxvif <- max(vif)
  cat("Maximum VIF = ", maxvif, "\n\n")
  meanvif <- mean(vif)
  cat("Mean VIF = ", meanvif, "\n\n")
}
VIF(finaldataY)
pairs(finaldataY)
cor(finaldataY)


