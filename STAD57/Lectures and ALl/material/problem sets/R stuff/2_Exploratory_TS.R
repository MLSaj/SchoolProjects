install.packages("astsa") # download textbook package
library(astsa) # load package


# Umbrella quarterly sales 

x=c(6.7,4.6,10,12.7,6.5,4.6,9.8,13.6,6.9,5,10.4,14.1,5,5.5,10.8,15,7.1,5.7,11.1,14.5,8,6.2,11.4,14.9)
x=ts(x,start=c(2001,1),frequency=4)	
?ts

out=lm( x~time(x) ) # estimate linear trend
summary(out) # model description
aov(out) # regression ANOVA table
AIC(out) # Akaike's information criterion
m=fitted(out) # extract regression's fitted values
m=ts(m,start=c(2001,1),frequency=4)	# convert fitted values to TS
y=x-m # y is de-trended series

plot(x, type='b', pch=16 ) 
lines(m, lwd=3, col=2)  # series w/ linear trend 

plot(y, type='b', pch=16, lwd=3 ) # de-trended series 

plot(diff(x,lag=4), type='b', pch=16, lwd=4 ) # lag-4 differenced series 


# Johnson & Johnson quarterly sales

n=length(jj)
x=1:n # explanatory variable is coded time: from 1 to n
x2=x^2 # squared time
out=lm( jj ~ x + x2 ) # quadratic regression 
m=fitted(out)
m=ts(m,start=start(jj),frequency=frequency(jj))
jjdt = jj-m # jjdt is de-trended series

plot(jj, xlab='', ylab='', lwd=3 )
lines(m, lwd=3, col=2)

plot(jjdt, xlab='', ylab='', lwd=3 )

logjj=log(jj) # apply nonlinear log transform
out=lm( logjj ~ x ) # linear regression 
m=fitted(out)
m=ts(m,start=start(jj),frequency=frequency(jj))
logjjdt = logjj-m

plot(logjj, xlab='', ylab='', lwd=3 )
lines(m, lwd=3, col=2)
plot(logjjdt, xlab='', ylab='', lwd=3 )


# Global average temperature 

plot(gtemp)
out=lm( gtemp~time(gtemp) ) # estimate linear trend
m=ts(fitted(out),start=start(gtemp),freq=frequency(gtemp)) 

plot(gtemp, lwd=2, xlab='' ) 
lines(m, lwd=3, col=2)  

gtempdt=gtemp-m # dt-trended series
plot(gtempdt, lwd=3)

gtempdif=diff(gtemp) # 1st order differenced series
plot(gtempdif, lwd=3)

acf(gtemp) # ACF's
acf(gtempdt)
acf(gtempdif)

