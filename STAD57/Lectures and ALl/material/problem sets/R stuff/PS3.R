#### 3.7 from text

ARMAacf(ar=c(-1.6,-.64), ma=0, 10)
ARMAacf(ar=c(.4,.45), ma=0, 10)
ARMAacf(ar=c(1.2,-.85), ma=0, 10)

#### 3.8 from text

phi=.6; theta=.9
AR_1.acf=ARMAacf(ar=phi, lag=25)
MA_1.acf=ARMAacf(ma=theta, lag=25)
ARMA_1.1.acf=ARMAacf(ar=phi, ma=theta, lag=25)

par(mfrow=c(1,3))
plot(AR_1.acf, type='h', main="AR(1) ACF", xla='lag', ylab='ACF' )
plot(MA_1.acf, type='h', main="MA(1) ACF", xla='lag', ylab='ACF' )
plot(ARMA_1.1.acf, type='h', main="ARMA(1,1) ACF", xla='lag', ylab='ACF' )
