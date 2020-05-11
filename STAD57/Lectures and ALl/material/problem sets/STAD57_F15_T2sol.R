# X=arima.sim(list(ar=c(.7,-.4,.5)) , 500)
# plot(X); acf(X); pacf(X)
# write.csv(X,"test2_data.csv")

#Q1
X=ts(read.csv('test_2_data.csv', header=FALSE))
plot(X)

#a.
acf(X); pacf(X)
# ACF tails-off; PACF cuts-off after lag 3 => AR(3) model

#b.
AR3.fit=arima(X,c(3,0,0))
AR3.pred=predict(AR3.fit,n.ahead=30)

#c.
plot(X,xlim=c(450,530),type='o', pch=20)
lines(AR3.pred$pred, col=2, pch=20, type='o')
lines(AR3.pred$pred+1.96*AR3.pred$se, col=3, pch=20, type='o')
lines(AR3.pred$pred-1.96*AR3.pred$se, col=3, pch=20, type='o')

#Q2

#a.
X.acf=ARMAacf(ar=c(-.6,.3), ma=c(-.5,.4), 50)
X.pacf=ARMAacf(ar=c(-.6,.3), ma=c(-.5,.4), 50, pacf=TRUE)
barplot(X.acf)
barplot(X.pacf)

#b.
X.MA=c(1,ARMAtoMA(ar=c(-.6,.3), ma=c(-.5,.4), 50))
barplot(X.MA)

#c.
# write model as W(t)=.5*W(t-1)-.4*W(t-2)+X(t)+.6*X(t-1)-.3*X(t-1)
# and find "causal" representation of W(t) w.r.t. "WN" X(t)
X.AR=c(1,ARMAtoMA(ar=c(.5,-.4), ma=c(.6,-.3), 50))
barplot(X.AR)


#d. 
# Since both models are defined w.r.t. the common WN {W(t)}
# the causal weights of their sum will add up
Y.MA=c(1,ARMAtoMA(ar=c(.5,.2), lag.max=50))
barplot(Y.MA+X.MA) # The ARMA 

#e.
# The variance of a causal series is equal to the sum of its 
# squared causal weights, multiplied with the WN variance
XY.var=sum( (Y.MA+X.MA)^2 )
