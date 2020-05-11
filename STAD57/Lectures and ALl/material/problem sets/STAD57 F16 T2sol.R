rm(lis=ls())
#Q1
X=ts(read.csv('test2_data.csv', header=FALSE))
plot(X)

#a.
acf(X); pacf(X)
# PACF tails-off; ACF cuts-off after lag 2 => MA(2) model

#b.
MA2.fit=arima(X,c(1,0,0))
MA2.pred=predict(MA2.fit,n.ahead=30)

plot(X,xlim=c(450,530),type='o', pch=20)
lines(MA2.pred$pred, col=2, pch=20, type='o')
lines(MA2.pred$pred+1.96*MA2.pred$se, col=3, pch=20, type='o')
lines(MA2.pred$pred-1.96*MA2.pred$se, col=3, pch=20, type='o')

#c.
# long-range predictions converge to series' mean 
MA2.fit$coef["intercept"]


#Q2 

#a.
N=1000; W=rnorm(N); V=rnorm(N)
X=filter(W, .75, method="recursive")
Y=filter(V, -.75, method="recursive")

# or, simpler
# X=arima.sim(list(ar=.75),1000)
# Y=arima.sim(list(ar=-.75),1000)


#b.
Z=X+Y
acf(Z); pacf(Z)
fitZ=arima(Z,order=c(2,0,0))

#c. 
Zpred=predict(fitZ,n.ahead=30)$pred

#d.
fitX=ar.yw(X,order.max = 1)
fitY=ar.yw(Y,order.max = 1)

Xpred=predict(fitX,n.ahead=30)$pred
Ypred=predict(fitY,n.ahead=30)$pred

plot(Xpred+Ypred)
lines(Zpred, col=2)
legend("topright", c("X_pred + Y_pred","Z_pred"), col=1:2, pch=19)
