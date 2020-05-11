#### 1. ####

my_data=read.csv("ontario_marriages.csv")
X=aggregate(COUNT~MONTH+YEAR, data=my_data, sum, subset= (CITY %in% c('TORONTO','OTTAWA')))

my_data %>% 
  filter(CITY %in% c("TORONTO", "OTTAWA")) %>% 
  group_by( YEAR, MONTH ) %>% 
  summarise( COUNT = sum( COUNT ))
  select(MONTH, YEAR, COUNT)

idx=(X$YEAR>=1990)
marriages=ts(X$COUNT[idx],start=c(1990,1), frequency=12)
plot(marriages, type='o', pch=20)



