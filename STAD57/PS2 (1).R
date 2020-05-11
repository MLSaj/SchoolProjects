#### Q1

W=rnorm(n=400, mean=0, sd=1)

# a.
X=filter(W, c(1,2,-1), sides=1)
par(mfrow=c(1,2))
plot(X,type='o',pch=20, main="TS Plot")
acf(X, na.action = na.pass, main="ACF Plot")

# b.
X=filter(W, c(-.5,.4), method = "recursive")
plot(X,type='o',pch=20, main="TS Plot")
acf(X, na.action = na.pass, main="ACF Plot")

# c.
X=filter(W+.01, c(1), method = "recursive")
plot(X,type='o',pch=20, main="TS Plot")
acf(X, na.action = na.pass, main="ACF Plot")


#### Q2

X=read.csv("Canada reserves.csv")
X1=ts(X[,2], start=c(1957,1), freq=12)

par(mfrow=c(2,2))
plot(X1, main="Original TS")
acf(X1, main="Original ACF")

X1.stationary=diff(log(X1))
plot(X1.stationary, main="Stationary TS")
acf(X1.stationary, main="Processed ACF" )

X=read.csv("Quebec car sales.csv")
X2=ts(X[,2], start=c(1960,1), freq=12)

plot(X2, main="Original TS")
acf(X2, main="Original ACF")

T1=time(X2) # explanatory variable for linear trend
T2=factor( round((T1%%1)*12) +1 ) # explanatory factor for (additive) monthly seasonality
out=lm(X2~T1+T2)
X2.stationary=ts( residuals(out), start=c(1960,1), freq=12)
plot(X2.stationary, main="Stationary TS")
acf(X2.stationary, main="Stationary ACF")

par(mfrow=c(1,1))
plot(X2, type='o', pch=20)
lines( ts(out$fitted, start=c(1960,1), freq=12), col=3, lwd=2 )
out.trend=lm(X2~T1)
lines( ts(out.trend$fitted, start=c(1960,1), freq=12), col=2, lwd=2 )
points(X2, type='o', pch=20)
legend('topleft',c("original",'trend','trend+seasonality'), col=1:3, lwd=rep(2,3), bty='n')

X=read.csv("daily Toronto temp.csv")
X3=ts(X[,2], start=c(2011,1), freq=365)

par(mfrow=c(2,2))
plot(X3, main="Original TS")
acf(X3, na.action=na.pass, main="Original ACF")

X3.stationary=(diff(X3, lag=365))
plot(X3.stationary, main="Stationary TS")
acf(X3.stationary,na.action=na.pass, main="Stationary ACF")
