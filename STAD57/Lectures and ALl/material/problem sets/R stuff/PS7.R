library(astsa)
library(forecast)

#Q3.31

X=diff(log(gnp))
plot(X)
sarima(X,1,0,0)

#Q3.32

plot(oil)
acf(oil); pacf(oil)

X=diff(log(oil))
layout(matrix(c(1,1,2,3), 2, 2, byrow = TRUE))
par(mar=c(4,4,1,1))
plot(X, ylab="oil price growth rate")
acf(X, 120, main=""); pacf(X, 120, main="")

auto.arima(X, seasonal=FALSE)
out1=sarima(X,1,0,1)

ar.yw(X, 15, aic=TRUE)
out2=sarima(X,8,0,0)


#Q3.33

plot(gtemp); acf(gtemp); pacf(gtemp)
plot(diff(gtemp)); acf(diff(gtemp)); pacf(diff(gtemp))

p_max=q_max=7; aic = matrix( 10^(1000), p_max+1, q_max+1) 

for(p in 0:p_max){ for(q in 0:q_max){
  aic[p+1,q+1] = (sarima(gtemp,p,1,q))$AIC }}

p_best=which.min( apply(aic,1,min) ) -1 
q_best=which.min( apply(aic,2,min) ) -1 

fit=sarima(gtemp,p_best,1,q_best)

fore = sarima.for(gtemp, n.ahead=10, p_best, 1, q_best)

plot( window(gtemp, start=1980, end=2009), type='o', pch=16,
      lwd=2, xlim=c(1980,2020), ylim=c(0,.9), ylab='gtemp')
lines(2010:2019,fore$pred, type='o', pch=16, col=2)
lines(2010:2019,fore$pred + 1.96*fore$se, lty=2, lwd=2, col=3)
lines(2010:2019,fore$pred - 1.96*fore$se, lty=2, lwd=2, col=3)


#Q3.41

par(mfrow=c(1,3),mar=c(2,2,1.5,2))
plot(unemp); acf(unemp); pacf(unemp)
plot(diff(unemp)); acf(diff(unemp)); pacf(diff(unemp))

fit=auto.arima(unemp,d=1)

fore=forecast(fit,12)

plot( window(unemp, start=c(1975,1), end=c(1978,12)), type='o', pch=16,
      lwd=2, xlim=c(1975,1980), ylim=c(300,900), ylab='unemp')
lines(fore$mean, type='o', pch=16, col=2, lwd=2)
lines(ts(fore$lower[,2],start=c(1979,1),freq=12), lty=2, lwd=2, col=3)
lines(ts(fore$upper[,2],start=c(1979,1),freq=12), lty=2, lwd=2, col=3)

#Q3.44

arma.fit=auto.arima(log(jj)) 
# selected SARIMA(2,0,2)x(0,1,0)[4] with drift

Dljj=diff(log(jj), lag=4) # seasonally differenced log-series at lag 4
plot(Dljj); acf(Dljj); pacf(Dljj)

sarima( log(jj), 2,0,2,0,1,0,4)
fore = sarima.for( log(jj), n.ahead=4, 2,0,2,0,1,0,4)

plot( window(jj, start=c(1975,1), end=c(1980,4)), type='o', pch=16,
      lwd=2, xlim=c(1974,1982), ylim=c(5, 23), ylab='jj')
lines(1981+c(0:3)/4,exp(fore$pred), type='o', pch=16, col=2)
lines(1981+c(0:3)/4,exp(fore$pred + 1.96*fore$se), lty=2, lwd=2, col=3)
lines(1981+c(0:3)/4,exp(fore$pred - 1.96*fore$se), lty=2, lwd=2, col=3)
