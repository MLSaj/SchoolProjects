### Finding PACF of ARMA models

phi_hh=ARMAacf(ar=c(.7,-.6), ma=c(.5,-.2), lag.max=20, pacf=TRUE)
plot(phi_hh, type='h'); abline(h=0)


AR=c(-1.5,-.6)
MA=c(0)

rho=ARMAacf(ar=AR, ma=MA, lag.max=20)
phi_hh=ARMAacf(ar=AR, ma=MA, lag.max=20, pacf=TRUE)
par(mfrow=c(1,2), mar=c(2,2,2,2))
plot(0:20,rho, type='h', lwd=3); abline(h=0)
plot(1:20,phi_hh, type='h', lwd=3); abline(h=0)


AR=c(1.5,-.6)
MA=c(-.8,-.5,.1)

rho=ARMAacf(ar=AR, ma=MA, lag.max=20)
phi_hh=ARMAacf(ar=AR, ma=MA, lag.max=20, pacf=TRUE)
par(mfrow=c(1,2), mar=c(2,2,2,2))
plot(0:20,rho, type='h', lwd=3); abline(h=0)
plot(1:20,phi_hh, type='h', lwd=3); abline(h=0)


AR=c(0)
MA=c(.8,-.5,.2)

rho=ARMAacf(ar=AR, ma=MA, lag.max=20)
phi_hh=ARMAacf(ar=AR, ma=MA, lag.max=20, pacf=TRUE)
par(mfrow=c(1,2), mar=c(2,2,2,2))
plot(0:20, rho, type='h', lwd=3); abline(h=0)
plot(1:20,phi_hh, type='h', lwd=3); abline(h=0)


