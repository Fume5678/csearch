# Anezka search

Simple search engine for database written on C++20 with gRPC interface


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

## Config file example
The yaml syntax is used for configuration
```
# config.yaml
version: "0.1"

app:
  host: "0.0.0.0:50051"

data:
  index_type: integer
  min_key_len: 3

indexer:
  source: postgres
  host: localhost
  port: 5432
  user: postgres
  password: postgres
  dbname:  book_db
  content:
    table: books
    index: id
    key_columns:
      - "title"
      - "description"
```

## gRPC api
| **Service**         | **Method**    | **Type**      | **Example Input**                                                | **Example Output**                                               |
|---------------------|---------------|---------------|------------------------------------------------------------------|------------------------------------------------------------------|
| IndexStorageService | Insert        | single-single | { "key": "word" "indexes": [ { "i_ind": 1 }, { "i_ind": 23 } ] } | {}                                                               |
|                     | GetIndexes    | single-single | { "key": "word" }                                                | { "key": "word" "indexes": [ { "i_ind": 1 }, { "i_ind": 23 } ] } |
| SearchService       | SearchIndex   | single-single | { "text": "novel Leo" }                                          | { "indexes": [  { "i_ind": 12 }, { "i_ind":35 } ] }              |
|                     | StreamSuggest | stream-stream | { "text": "lo" }                                                 | {"text": "love"}; {"text": "lord"}; {"text": "longboard"}; ...   |
