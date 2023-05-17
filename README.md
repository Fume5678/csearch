# Anezka search

Simple search engine for database written on C++20


## Build guide
```
  git clone https://github.com/nselyavin/anezkasearch
  
  # For grpc and its submodules
  git submodule update --init --recursive
  
  mkdir -p build & cd build
  cmake ..
  make protoc
  make plugins
  
  # Generate protos
  ../CompileProtos.sh
  
   make anezkasearch_exe
  
  # Run anezkasearch with config file 
  ./anezkasearch -f anezka-config.yaml
```
