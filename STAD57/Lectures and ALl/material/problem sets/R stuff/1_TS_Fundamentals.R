install.packages("astsa") # download textbook package
library(astsa) # load package

plot(gtemp) # Global mean temperature

acf(soi) # ACF

plot(gtemp) # plot global average temperature (gtemp)

w=7
smooth.gtemp=filter(gtemp, rep(1/w,w))

lines(smooth.gtemp, col=2)
