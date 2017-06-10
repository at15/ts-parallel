# Wakatime

JSON dumped from https://wakatime.com/

Questions to answer

- the file that cost most time in one day
  - sort by the edit_duration without any grouping
- sort projects by the total time spent on it
  - `select project, SUM(edit_duration) as sd group by project order by sd desc` 
- time spent on a specific project group by file name sort by time desc
  - `select file, SUM(edit_duration) as sd where project = 'Ayi' group by file order by sd desc`
- moving average on every day
- moving average on every month
- histogram

Amplifier

- add data that has little weight to make the data much larger
- multi user system?

TODO:

- How to sort two vectors in parallel, std::sort only have compare function, no swap function
    - thrust provide sort by key `thrust::sort_by_key`

Sort By Key

- https://stackoverflow.com/questions/17074324/how-can-i-sort-two-vectors-in-the-same-way-with-criteria-that-uses-only-one-of
  - build a permutation (array index), sort by key to get a sorted permutation and apply to get the new sorted
- https://stackoverflow.com/questions/236172/how-do-i-sort-a-stdvector-by-the-values-of-a-different-stdvector
  - use a tuple

Thrust

- OMP https://github.com/thrust/thrust/blob/master/thrust/system/omp/detail/sort.inl
- CUDA? 
  - https://github.com/thrust/thrust/blob/master/thrust/system/detail/sequential/sort.inl
  - https://github.com/thrust/thrust/blob/master/thrust/system/detail/sequential/stable_merge_sort.inl

ArrayFire

- CPU https://github.com/arrayfire/arrayfire/blob/devel/src/backend/cpu/kernel/sort_by_key_impl.hpp
  - call `std::sort`, change k,v into tuple `<k,v>`
  - [ ] TODO: why it called `stable_sort` twice? it sort both key and value?
- CUDA, seems to be using Thrust ...
  - https://github.com/arrayfire/arrayfire/blob/devel/src/backend/cuda/sort_by_key.cu
    - https://github.com/arrayfire/arrayfire/blob/devel/src/backend/cuda/kernel/sort_by_key.hpp

Histogram 

ArrayFire 

- CUDA 
  - https://github.com/arrayfire/arrayfire/blob/devel/src/backend/cuda/kernel/histogram.hpp    