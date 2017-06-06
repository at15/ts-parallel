# Spark

- https://spark.apache.org/docs/latest/sql-programming-guide.html
  - https://spark.apache.org/docs/latest/sql-programming-guide.html#data-sources
- https://dzone.com/articles/processing-csv-files-using-databricks-spark-csv-li
- http://localhost:4040/stages/ it will show the time of all the queries

## Dataframe

Import CSV data

````scala
import org.apache.spark.sql.SparkSession
val spark = SparkSession.builder().appName("Spark SQL basic example").config("spark.some.config.option", "some-value").getOrCreate()
import spark.implicits._
val df = spark.read.format("csv").option("header", "true").option("inferSchema", "true").load("/home/at15/workspace/src/github.com/at15/ts-parallel/playground/csv/prices-split-adjusted.csv")
df.printSchema()
````

Count symbols

````scala
df.select("symbol").distinct().count()
````

Group by symbols

````scala
df.groupBy("symbol").count().show()
````

````
501
````

Average closing price per year (from mapr)

````scala
df.select(year($"date").alias("yr"), $"close").groupBy("yr").avg("close").orderBy(desc("yr")).show()
````

````
+----+------------------+                                                       
|  yr|        avg(close)|
+----+------------------+
|2016| 84.94332928181187|
|2015|   83.917471861779|
|2014| 77.20991259159842|
|2013| 64.15859588134416|
|2012|52.938396554760814|
|2011| 48.01073535235524|
|2010| 40.92528393074817|
+----+------------------+
````

````scala
// without option, header will be treated as data
val df = spark.read.csv("/home/at15/workspace/src/github.com/at15/ts-parallel/playground/csv/prices-split-adjusted.csv")
// read json from official example
spark.read.format("json").load("examples/src/main/resources/people.json")
````
