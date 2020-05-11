library(astsa)

## Simulated Integrated Series

x=cumsum(rnorm(500)) # integrated of order 1
plot(x, type='l')
acf(x) 
acf(diff(x)) 

y=cumsum(x) # integrated of order 2
plot(y, type='l')
acf(y) 
acf(diff(y,differences=2))
acf(diff(y,2)) # this is NOT 2nd order difference, but difference at lag 2 -> not stationary

## ARIMA estimation/forecasting for GNP series

par(mfrow=c(1,2))
plot(gnp); plot(log(gnp))

y=log(gnp) # log-transform

par(mfrow=c(2,2))
plot(y); plot(diff(y))
acf(y); acf(diff(y))

par(mfrow=c(1,2))
acf(diff(y)); pacf(diff(y))

# Fit ARIMA(0,1,2)
fit_ma = sarima(y,0,1,2)
fit_ma

# Forecasts from fitted ARIMA(0,1,2) model
fore = sarima.for(log(gnp), n.ahead=20, 0, 1, 2)

plot( window( gnp, c(1990,1), end(gnp) ), lwd=2, 
      xlim=c(1990,2008), ylim=c(6500,13000), ylab='GNP')
lines(exp(fore$pred), type='p', pch=16, col=2)
lines(exp(fore$pred + 1.96*fore$se ), lty=2, lwd=2, col=3)
lines(exp(fore$pred - 1.96*fore$se ), lty=2, lwd=2, col=3)

### Diagnostics for GNP series ARIMA model

y=log(gnp)
fit_ma = sarima(y,0,1,2) ## MA(2) estimation for GNP series

# Extract model residuals
res = fit_ma$fit$res
stdres = fit_ma$fit$res / sqrt(fit_ma$fit$sigma2)

plot(stdres) # residual plot
qqnorm(stdres); qqline(stdres) # normal QQ-plot
acf(stdres) # residual ACF
Box.test(stdres, 20) # Ljung-Box test (H=20) 

### SARIMA models ###

# US Production data

par(mfrow=c(1,1))
plot(prodn)
par(mfrow=c(1,2))
acf(prodn,60); pacf(prodn,60)

dprodn=diff(prodn) # differenced series
par(mfrow=c(1,1))
plot(dprodn)
par(mfrow=c(1,2))
acf(dprodn,60); pacf(dprodn,60)

ddprodn=diff(dprodn,lag=12) # lag-12 differences of differenced series
par(mfrow=c(1,1))
plot(ddprodn)
par(mfrow=c(1,2))
acf(ddprodn,60); pacf(ddprodn,60)

sarima(prodn, 2, 1, 0, 0, 1, 3, 12)
sarima.for(prodn, 20, 2, 1, 0, 0, 1, 3, 12)


### Using auto.arima ###

library(forecast)

# US Production data

auto.arima(prodn, d=1, D=1)
sarima(prodn,1,1,1,0,1,1,12)
sarima.for(prodn, 20, 1, 1, 1, 0, 1, 1, 12)


## Monthly total international airline passengers (1949 to 1960)

plot(AirPassengers)

lAP = log(AirPassengers) # take log-transform to stabilize variance
par(mfrow=c(1,1))
plot(lAP)

par(mfrow=c(1,2))
acf(lAP,50); pacf(lAP,50)

# first order differences
dlAP=diff(lAP)
par(mfrow=c(1,1))
plot(dlAP,type='l')

par(mfrow=c(1,2))
acf(dlAP, 50);pacf(dlAP, 50)

# first order seasonal differences w/ period s=12
d12dlAP=diff(dlAP,lag=12)
par(mfrow=c(1,1))
plot(d12dlAP,type='l')

par(mfrow=c(1,2))
acf(d12dlAP, 50);pacf(d12dlAP, 50)

auto.arima(lAP, ic="bic")
auto.arima(lAP, d=1, D=1, ic="aic")
par(mfrow=c(1,1))
plot(forecast(fit,h=20))

sarima(lAP,0,1,1,0,1,1,12)
sarima.for(lAP,20,0,1,1,0,1,1,12)

sarima.for(lAP,60,0,1,1,0,1,1,12)


