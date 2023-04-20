 #!/bin/bash

echo "Start compiling process"
echo `protoc --version`

protos_path=./protos
protos_headers_path=./protos-gen
protos_sources_path=./protos-gen

for protos_file in "$protos_path"/*
do
    echo Compile: $protos_file
    protoc -I $protos_path --grpc_out=$protos_headers_path --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $protos_file
    protoc -I $protos_path --cpp_out=$protos_headers_path $protos_file
done

echo "Compiling is done"
