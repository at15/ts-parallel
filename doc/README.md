# Documentation

- [Stock related](stock)

## TODO

### in memory database tuple representation

- need to figure out what data structure to use if we want to have a row based representation
  - it's quite simple to have column based representation, just an map of arrays
- http://15721.courses.cs.cmu.edu/spring2017/slides/02-inmemory.pdf
  - operator at a time (instead of tuple at a time)
  - vector at a time
- https://hpi.de/fileadmin/user_upload/fachgebiete/plattner/teaching/TrendsandConcepts/2010/Krueger_DataStructuresForIMDBs.pptx.pdf
  - talks about row vs column, encoding etc.
- seems need to allocate a large array and use index instead of using `std:tuple`

### comparison

Timescale

InfluxDB (if it supports the query)

Druid (if I can set it up)

Spark

Hadoop

Kudu / Impala?

Apache Arrow?

### data set

- Passenger Dataset from SFO Air Traffic Statistics
  - https://drill.apache.org/docs/text-files-csv-tsv-psv/#how-to-convert-csv-to-parquet
- Timescale weather and devices https://docs.timescale.com/other-sample-datasets

## CSV

- https://github.com/ben-strasser/fast-cpp-csv-parser
  - std setvbuf disable system buffering
  - http://man7.org/linux/man-pages/man3/setbuf.3.html
  - std::move http://en.cppreference.com/w/cpp/utility/move
- https://github.com/antonmks/nvParse
  - there is a GPU based csv parser ...
  
## sort

- https://stackoverflow.com/questions/3969813/which-parallel-sorting-algorithm-has-the-best-average-case-performance

## cpp

Network

- https://github.com/ipkn/crow Crow is very fast and easy to use C++ micro web framework (inspired by Python Flask)
  - built in json support
- https://github.com/chenshuo/muduo
- https://github.com/yedf/handy 简洁易用的C++11网络库 / 支持单机千万并发连接

## Ref

- [Book] A Course in In-Memory Data Management
- https://databricks.com/blog/2015/04/28/project-tungsten-bringing-spark-closer-to-bare-metal.html
