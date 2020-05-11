library("astsa")

### Finding psi-weights of ARMA models

psi = ARMAtoMA(ar=c(.7,-.6), ma=c(.5,-.2), lag.max=10)
barplot(psi, names=1:10)

### Finding ACF of ARMA models

ARMAacf(ar=c(.5,-.3),lag.max=3) # example from slide 10

rho=ARMAacf(ar=c(.7,-.6), ma=c(.5,-.2), lag.max=20)
plot(rho, type='h'); abline(h=0)

