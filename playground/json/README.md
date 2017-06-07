# JSON

JSON dump from wakatime

- users (obj)
- range (obj)
  - start (timestamp)
  - end
- days (array)
  - date
  - editors (array)
    - total_seconds
    - name
    - percent
  - entities (array) // all the files, there are duplication in later branches
    - name
    - type (file is the only one I've seen so far)
    - total_seconds
  - grand_total (obj)
    - total_seconds
  - languages (array)
    - name
    - total_seconds
  - operating_systems (array)
    - name
    - total_seconds
  - projects (array) // the structure is similar to the outer level
    - name
    - branches (array)
    - editors (array)
    - entities (array)
    - operating_system (array)
    - grand_total (obj)
    - languages (array)    

## CPP

- https://github.com/miloyip/nativejson-benchmark    