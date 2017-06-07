# GRPC

- https://github.com/IvanSafonov/grpc-cmake-example

Install GRPC
- location is `/usr/local/include`

````
Ayi git clone https://github.com/grpc/grpc
cd ~/workspace/src/github.com/grpc/grpc
git submodule update --init
make
sudo make install
````

Install Protobuf
- location is `/usr/local/include/google/protobuf/`

````
Ayi git clone https://github.com/google/protobuf
cd ~/worskspace/src/github.com/google/protobuf
./autogen.sh
./configure
make
make check
sudo make install
sudo ldconfig
````

Build the example in `examples/cpp/helloworld`

````
[INSTALL] Installing public C headers
[MAKE]    Generating cache.mk
[STRIP]   Stripping libgpr.a
[STRIP]   Stripping libgrpc.a
[STRIP]   Stripping libgrpc_cronet.a
[STRIP]   Stripping libgrpc_unsecure.a
[INSTALL] Installing C pkg-config files
[INSTALL] Installing libgpr.a
[INSTALL] Installing libgrpc.a
[INSTALL] Installing libgrpc_cronet.a
[INSTALL] Installing libgrpc_unsecure.a
[STRIP]   Stripping libgpr.so.4.0.0-dev
[STRIP]   Stripping libgrpc.so.4.0.0-dev
[STRIP]   Stripping libgrpc_cronet.so.4.0.0-dev
[STRIP]   Stripping libgrpc_unsecure.so.4.0.0-dev
[INSTALL] Installing libgpr.so.4.0.0-dev
[INSTALL] Installing libgrpc.so.4.0.0-dev
[INSTALL] Installing libgrpc_cronet.so.4.0.0-dev
[INSTALL] Installing libgrpc_unsecure.so.4.0.0-dev
/sbin/ldconfig.real: /usr/lib/nvidia-375/libEGL.so.1 is not a symbolic link

/sbin/ldconfig.real: /usr/lib32/nvidia-375/libEGL.so.1 is not a symbolic link

[INSTALL] Installing public C++ headers
[STRIP]   Stripping libgrpc++.a
[STRIP]   Stripping libgrpc++_cronet.a
[STRIP]   Stripping libgrpc++_error_details.a
[STRIP]   Stripping libgrpc++_reflection.a
[STRIP]   Stripping libgrpc++_unsecure.a
[INSTALL] Installing C++ pkg-config files
[INSTALL] Installing libgrpc++.a
[INSTALL] Installing libgrpc++_cronet.a
[INSTALL] Installing libgrpc++_error_details.a
[INSTALL] Installing libgrpc++_reflection.a
[INSTALL] Installing libgrpc++_unsecure.a
[STRIP]   Stripping libgrpc++.so.1.5.0-dev
[STRIP]   Stripping libgrpc++_cronet.so.1.5.0-dev
[STRIP]   Stripping libgrpc++_error_details.so.1.5.0-dev
[STRIP]   Stripping libgrpc++_reflection.so.1.5.0-dev
[STRIP]   Stripping libgrpc++_unsecure.so.1.5.0-dev
[INSTALL] Installing libgrpc++.so.1.5.0-dev
[INSTALL] Installing libgrpc++_cronet.so.1.5.0-dev
[INSTALL] Installing libgrpc++_error_details.so.1.5.0-dev
[INSTALL] Installing libgrpc++_reflection.so.1.5.0-dev
[INSTALL] Installing libgrpc++_unsecure.so.1.5.0-dev
/sbin/ldconfig.real: /usr/lib/nvidia-375/libEGL.so.1 is not a symbolic link

/sbin/ldconfig.real: /usr/lib32/nvidia-375/libEGL.so.1 is not a symbolic link

[INSTALL] Installing grpc protoc plugins
[INSTALL] Installing root certificates
````
