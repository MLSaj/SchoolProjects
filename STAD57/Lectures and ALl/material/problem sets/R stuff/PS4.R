# Q3.10 from textbook

#install.packages("astsa") # package for textbook data & functions (run only once)
library(astsa) # load package

#a. 
(AR2.ols=ar.ols(cmort, order=2, demean=FALSE, intercept=TRUE)) # fit AR(2) w/ OLS

#b.
AR2.pred=predict(AR2.ols, n.ahead=4) # create predictions

pred.mean=AR2.pred$pred # prediction mean
pred.upper95PI=AR2.pred$pred+qnorm(1-.05/2)*AR2.pred$se # 95% Confidence interval
pred.lower95PI=AR2.pred$pred-qnorm(1-.05/2)*AR2.pred$se

plot(cmort, xlim=c(1978.5,1979.85), ylim=c(70,110), type='o', pch=20)
lines(pred.mean, col=2, lwd=2, type='o', pch=20)
lines(pred.upper95PI, col=3, lwd=2, type='o', pch=20)
lines(pred.lower95PI, col=3, lwd=2, type='o', pch=20)
legend('topleft', c("forecast",'95% pred-int'), col=2:3, pch=15)

# Q8

#a.
X=read.csv("Canada reserves.csv")
X1=ts(X[,2], start=c(1957,1), freq=12)
X1.stationary=diff(log(X1))

par(mfrow=c(1,2))
acf(X1.stationary, main="ACF")
acf(X1.stationary, type='partial', main='PACF')

#b.
X=read.csv("Quebec car sales.csv")
X2=ts(X[,2], start=c(1960,1), freq=12)
T1=time(X2)
T2=factor( round((T1%%1)*12) +1 ) 
out=lm(X2~T1+T2)
X2.stationary=ts( residuals(out), start=c(1960,1), freq=12)
acf(X2.stationary, main="ACF")
acf(X2.stationary, type='partial', main='PACF')

#c.
X=read.csv("daily Toronto temp.csv")
X3=ts(X[,2], start=c(2011,1), freq=365)
X3.stationary=(diff(X3, lag=365))
acf(X3.stationary, na.action=na.pass,  main="ACF")
acf(X3.stationary, na.action=na.pass, type='partial', main='PACF')
