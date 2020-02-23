# lzr : a laser commander


### To Build and Run
#### Install vcpkg
```
> git clone https://github.com/Microsoft/vcpkg.git
> cd vcpkg

PS> .\bootstrap-vcpkg.bat
Linux:~/$ ./bootstrap-vcpkg.sh
```

#### Install asio and abseil
```
PS> .\vcpkg install asio abseil
Linux:~/$ ./vcpkg install asio abseil
```

#### Clone and Build lzr
```
> git clone https://github.com/hellozee/lzr.git
> mkdir lzr/build
> cd lzr/build
> cmake .. -DCMAKE_TOOLCHAIN_FILE=<vcpkg_cmake_toolchain_file>
> cmake --build .
```

#### Running the executables
```
> ./bin/lzr-server #on the server machine
> ./bin/lzr-client <server-ip> #on the client machine
```