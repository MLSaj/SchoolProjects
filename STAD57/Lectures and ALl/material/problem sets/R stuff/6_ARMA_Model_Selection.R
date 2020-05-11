library(astsa)

### Model Selection

d.l.gnp=diff(log(gnp)) # GNP series
plot(gnp); acf(gnp, main="")
plot(d.l.gnp); acf(d.l.gnp, main="")
pacf(d.l.gnp, main="")

fit_ar = arima(d.l.gnp, order=c(1,0,0)) # Fit ARMA(1,0) 
fit_ma = arima(d.l.gnp ,order=c(0,0,2)) # Fit ARMA(0,2) 

AIC(fit_ar) # or equivalently: > fit_ar$aic
AIC(fit_ma) # ARMA(0,2)=MA(2) has smaller AIC

BIC(fit_ar) # ARMA(1,0)=AR(1) has smaller BIC
BIC(fit_ma) 

# Automatic model selection for AR models
ar(d.l.gnp, order.max=20, aic=TRUE) # selects best AR(p) model from p=1,...,20, using AIC

# Automatic model selection for ARMA models
auto.arima(d.l.gnp)

### Diagnostics for GNP series ARMA model
fit_ma = arima(d.l.gnp ,order=c(0,0,2)) # Fit ARMA(0,2) 

# Extract model residuals
res = fit_ma$residuals
stdres = fit_ma$residuals / sqrt(fit_ma$sigma2)

plot(stdres) # residual plot
qqnorm(stdres); qqline(stdres) # normal QQ-plot
acf(stdres) # residual ACF
Box.test(stdres, lag=20) # Ljung-Box test (H=20) 

lags=3:20; p.values=rep(0,length(lags))
for(i in 1:length(lags)){
  p.values[i]=Box.test(stdres, lags[i], type = "Ljung-Box")$p.value
}
plot(lags, p.values, ylim=c(0,1), main="Ljung-Box p-values"); abline(h=.05, lty=2)

