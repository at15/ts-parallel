# Using Apache Spark SQL to Explore S&P 500, and Oil Stock Prices

https://mapr.com/blog/using-apache-spark-sql-explore-sp-500-and-oil-stock-prices/

## Questions to answer

- Compute the average closing price per year for SPY, XOM, APC
- Compute the average closing price per month for SPY, XOM, APC
- List the number of times the closing price for SPY went up or down by more than 2 dollars
- Compute the Statistical correllation between XOM and SPY

## Sample code

well, the example code is actually outdated since spark has built in support for csv

````scala
import org.apache.spark._
import org.apache.spark.rdd.RDD
import org.apache.spark.util.IntParam
import org.apache.spark.sql.SQLContext
import org.apache.spark.sql.functions._
import org.apache.spark.sql.types._
import org.apache.spark.sql._
import org.apache.spark.mllib.stat.Statistics
val sqlContext = new org.apache.spark.sql.SQLContext(sc)
import sqlContext.implicits._
import sqlContext._
//define the schema using a case class
case class Stock(dt: String, openprice: Double, highprice: Double, lowprice: Double, closeprice: Double,
  volume: Double, adjcloseprice: Double)
//split a String by comma into an array of Strings, create and return a Stock object from the array</font>
def parseStock(str: String): Stock = {
  val line = str.split(",")
  Stock(line(0), line(1).toDouble, line(2).toDouble, line(3).toDouble, line(4).toDouble, line(5).toDouble,
    line(6).toDouble)
}
//  skip the header, parse each String element in the RDD into a Stock object</font>
def parseRDD(rdd: RDD[String]): RDD[Stock] = {
    val header = rdd.first
    rdd.filter(_(0) != header(0)).map(parseStock).cache()
}
val stocksDF = parseRDD(sc.textFile("spytable.csv")).toDF.cache()
stocksDF.show()
stocksDF.printSchema()
````

````scala
// Compute the average closing price per year for SPY
stocksDF.select(year($"dt").alias("yr"), $"adjcloseprice").groupBy("yr").avg("adjcloseprice").orderBy(desc("yr")).show()
````
