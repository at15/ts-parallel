# Kaggle S&P 500

https://www.kaggle.com/dgawlik/nyse

prices.csv (50M)

- volume
  - money traded
- There have been approx. 140 stock splits in that time, this set doesn't account for that.
  - lower the price of single uint by having more stocks
  - http://www.investopedia.com/ask/answers/113.asp

````
date,symbol,open,close,low,high,volume
2016-01-05 00:00:00,WLTW,123.43,125.839996,122.309998,126.25,2163600.0
````

prices-split-adjusted (51M)

- 'same as prices, but there have been added adjustments for splits'
  - [ ] how adjusted

securities

````
"Ticker symbol","Security","SEC filings","GICS Sector","GICS Sub Industry","Address of Headquarters","Date first added","CIK"
"ADBE","Adobe Systems Inc","reports","Information Technology","Application Software","San Jose, California","1997-05-05","0000796343"
````

fundamentals

- `metrics extracted from annual SEC 10K fillings`
