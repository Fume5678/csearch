//
// Created by fume on 27.04.23.
//

#include "http/GrpcServiceImpl.h"

grpc::Status anezkasearch::GrpcServiceImpl::InsertIndex(
    ::grpc::ServerContext* context, const ::anezkasearch::KeyIndexes* request,
    ::anezkasearch::KeyIndexes* response) {
  

  return Service::InsertIndex(context, request, response);
}

grpc::Status anezkasearch::GrpcServiceImpl::GetIndexes(
    ::grpc::ServerContext* context, const ::anezkasearch::KeyIndexes* request,
    ::anezkasearch::KeyIndexes* response) {
  return Service::GetIndexes(context, request, response);
}

grpc::Status anezkasearch::GrpcServiceImpl::RemoveIndex(
    ::grpc::ServerContext* context, const ::anezkasearch::KeyIndexes* request,
    ::anezkasearch::KeyIndexes* response) {

  return Service::RemoveIndex(context, request, response);
}
