library(astsa) # for rec & soi data
library(vars) # for fitting VAR models

X=cbind(rec,soi)
plot(X, main="")
acf(X,lag=100)

#fitting VAR(p) model

VARselect(X,lag.max=20) #best AIC @ lag p=15
out=VAR(X,15) 
summary(out)

pred=predict(out,n.ahead=24)
fanchart(pred, cis=.95,colors=2)

library(dse) # for simulating VAR models

# Simulate VAR(2)-data; using package 'dse'
Apoly=array(0,c(2,2,2)) ## Setting AR matrices
Apoly[1,,]=diag(2)
Apoly[2,,]=matrix( c(-.7,0,-0.7,-.7),2,2)
B=diag(2)
# Generating the VAR(2) model 
var2=ARMA(A = Apoly, B = B)
# Simulating 500 observations
varsim=simulate(var2, sampleT = 500, 
                noise = list(w = matrix(rnorm(1000),nrow = 500, ncol = 2))) 

Y=ts(varsim$output)
colnames(Y)=c("X1","X2")
plot(Y,main="") 

acf(Y)
out=VAR(Y,1)

# Granger Causality test
causality(out, cause='X1')

#impulse response function
out.irf=irf(out, ortho=FALSE)
plot(out.irf)

# Cointegration analysis
X=read.table('yield_rates.txt', header=TRUE)

YR=ts(X[,-1], start= c(as.numeric(substr(X[1,1],1,4)),1), freq=12)
colnames(YR)=temp=gsub("T", "Y", gsub("FYG","",colnames(YR)))

Y=YR[,c("Y1","Y3")]
plot(Y , plot.type='single', col=1:2, lwd=2)
legend("topright",colnames(Y),col=1:2,lwd=2)

acf(Y,250)

dY=Y[,"Y1"]-Y[,"Y3"]
plot(dY, lwd=2)
acf(dY,250)

library(tseries) # For unit root tests
adf.test(Y[,"Y1"])
adf.test(Y[,"Y3"])
adf.test(dY)

# Engle-Granger approach
(out=lm(Y1~Y3,data=Y))
dY.est=residuals(out)
adf.test(dY.est)

plot(Y[,"Y3"],Y[,"Y1"])
abline(out, col=2,lwd=2)

library(urca) # for VECM models

out=ca.jo(Y, ecdet="const", K=3) # test for number of cointegrating relations 
summary(out)
cajorls(out,r=1) # estimate VECM with #r cointegrated vectors

# Find cointegration with 3 yield rates
Y.3D=YR[,c("Y1","Y3","Y5")]
out=ca.jo(Y.3D,ecdet="const",K=3)
summary(out) # two cointegrating vectors (r=2)
cajorls(out,r=2) 
# two cointegrating relations are, roughly 
# 1Y1 - 1.05Y5 = constant
# 1Y2 - 1.04Y5 = constant
# i.e. we have Y1 ~ Y3 ~ Y3


