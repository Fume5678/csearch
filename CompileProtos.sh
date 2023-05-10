 #!/bin/bash

echo "Start compiling process"
echo `./build/external/grpc/third_party/protobuf/protoc --version`

grpc_plugin_PATH=$(dirname "$0")/build/external/grpc/grpc_cpp_plugin
protos_path=$(dirname "$0")/protos
protos_headers_path=$(dirname "$0")/protos-gen
protos_sources_path=$(dirname "$0")/protos-gen
protoc=./build/external/grpc/third_party/protobuf/protoc

echo "grpc_plugin_PATH $grpc_plugin_PATH"

mkdir -p $protos_headers_path
mkdir -p $protos_sources_path

for protos_file in "$protos_path"/*
do
    echo Compile: $protos_file
    $protoc -I $protos_path --grpc_out=$protos_headers_path --plugin=protoc-gen-grpc=$grpc_plugin_PATH $protos_file
    $protoc -I $protos_path --cpp_out=$protos_headers_path $protos_file
done

echo "Compiling is done"
