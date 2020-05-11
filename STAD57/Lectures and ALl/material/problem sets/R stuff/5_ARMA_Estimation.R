library("astsa")

## Yule-Walker estimation

par(mfrow=c(1,2))
acf(rec); pacf(rec) 

yw.fit = ar.yw( rec, order=2)
yw.fit$x.mean
yw.fit$ar
yw.fit$var.pred
yw.fit$asy.var

## Forecasting from fitted model
forecast=predict(yw.fit, n.ahead=24)
forecast$pred
forecast$se

plot( window(rec, start=c(1982,1), end=end(rec)), xlim=c(1982,1989.5), ylim=c(-5,115), ylab='rec')
lines( forecast$pred, type='b', pch=16, col=2 )
lines( forecast$pred + 1.96 * forecast$se, lty=2, col=3, lwd=2 )
lines( forecast$pred - 1.96 * forecast$se, lty=2, col=3, lwd=2 )

## Maximum Likelihood estimation

ml.fit = ar.mle( rec, order=2)
ml.fit$x.mean
ml.fit$ar
ml.fit$var.pred
ml.fit$asy.var

## Least Squares estimation

ls.fit = ar.ols( rec, order=2 )
ls.fit$x.mean
ls.fit$ar
ls.fit$var.pred

## Southern Oscilation Index data
plot(soi)
par(mfrow=c(1,2))
acf(soi); pacf(soi) 

## ARMA ML estimation
ml.fit = arima(soi, order=c(2,0,2) ) # ARMA(2,2) model
ml.fit$coef
ml.fit$sigma2
ml.fit$var.coef

## ARMA LS estimation
ls.fit = arima(soi, order=c(2,0,2), method="CSS" )
ls.fit$coef
ls.fit$sigma2
ls.fit$var.coef

