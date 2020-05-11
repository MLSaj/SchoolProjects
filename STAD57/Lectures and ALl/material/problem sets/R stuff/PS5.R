#Q3.18
library(astsa)
plot(cmort)
fit.yw=ar.yw(cmort, aic=FALSE, order.max=2)
fit.ols=ar.ols(cmort, aic=FALSE, order.max=2)

#a.
fit.ols$ar
fit.yw$ar

#b.
fit.ols$asy.se.coef$ar
sqrt(diag(fit.yw$asy.var.coef))

#Q3.20
n=500; model=list(ar=.9, ma=-.9)
for(i in 1:3){
  X=arima.sim(model,n)
  acf(X); pacf(X)
}

#Q3.21
n=200; model=list(ar=.9, ma=.5)
for(i in 1:10){
  X=arima.sim(model,n)
  AR1MA1.fit=arima(X,order=c(1,0,1),include.mean=FALSE)
  print(AR1MA1.fit$coef); print(AR1MA1.fit$sigma2)
}

#Q3.22
n=50; model=list(ar=.99, ma=.5)
X=arima.sim(model,n)
fit.yw=ar.yw(X,order.max=1) # Yule-Walker estimation of phi

B=200; phi_hat=rep(0,B)  # Bootstrap simulation
for(i in 1:200){
  X=arima.sim(model,n)
  phi_hat[i]=ar.yw(X,order.max = 1)$ar
}

x=seq(min(phi_hat)*.9,max(phi_hat)*1.1,length=100)
plot(x, dnorm( x, mean=fit.yw$ar, sd = sqrt(fit.yw$asy.var.coef) ), 
     type='l' , xlab="phi", ylab = "density", ylim=c(0,10), lwd=2 )
lines(density(phi_hat), col=2, lwd=2)
legend('topleft',pch=19, col=c(1,2), legend=c("Asymp. Approximation", "Bootstrap Estimate"), bty ='n')

