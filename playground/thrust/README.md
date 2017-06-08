# Thrust

http://docs.nvidia.com/cuda/thrust/index.html#axzz4jMdjXi00

- https://github.com/thrust/thrust/tree/master/examples
- moving average https://github.com/thrust/thrust/blob/master/examples/simple_moving_average.cu
- run length encoding https://github.com/thrust/thrust/blob/master/examples/run_length_encoding.cu

## Vectors

- `thrust::host_vector`
- `thrust::device_vector`
- you can copy from host to/from device using `=`, but they **require call** to `cudaMemcpy`
- `H.begin()` returns a host iterator used by `thrust::fill`
- wrap raw pointer using `thrust::device_ptr`

````cpp
size_t N = 10;
// raw pointer to device memory
int * raw_ptr;
cudaMalloc((void **) &raw_ptr, N * sizeof(int));
// wrap raw pointer with a device_ptr
thrust::device_ptr<int> dev_ptr(raw_ptr);
// use device_ptr in thrust algorithms
thrust::fill(dev_ptr, dev_ptr + N, (int) 0);
````

````cpp
size_t N = 10;

// create a device_ptr
thrust::device_ptr<int> dev_ptr = thrust::device_malloc<int>(N);

// extract raw pointer from device_ptr
int * raw_ptr = thrust::raw_pointer_cast(dev_ptr);
````

## Algorithms

> With the exception of thrust::copy, which can copy data between host and device, all iterator arguments to a Thrust algorithm should live in the same place: either all on the host or all on the device. When this requirement is violated the compiler will produce an error message.

Functor https://stackoverflow.com/questions/356950/c-functors-and-their-uses
- allow compiler optimization

### Transform (Map)

- `thrust::transform`
  - f(x) -> y `thrust::transform(X.begin(), X.end(), Y.begin(), thrust::negate<int>());`
  - f(x, x) -> y `thrust::transform(X.begin(), X.end(), Z.begin(), Y.begin(), thrust::modulus<int>());`

````
struct saxpy_functor
{
  const float a;

  saxpy_functor(float _a) : a(_a) {}

  __host__ __device__
    float operator()(const float& x, const float& y) const {
      return a * x + y; }
    };
}
````

### Reductions

````
int sum = thrust::reduce(D.begin(), D.end(), (int) 0, thrust::plus<int>());
````

- `thrust::transform_reduce(d_x.begin(), d_x.end(), unary_op, init, binary_op)`

### Prefix Sums (Scan)

- inclusive_scan
  - data[2] = data[0] + data[1] + data[2]
- exclusive_scan
  - data[2] = data[0] + data[1]

### Reordering

- copy_if
- partition
  - divide into two parts (like partition in quick sort)
- remove, remove_if
- unique  

### Sort

- sort
- sort_by_key
- stable_sort

## Fancy Iterators

- constant_iterator
- counting_iterator
- transform_iterator
- permutation_iterator
- zip_iterator
