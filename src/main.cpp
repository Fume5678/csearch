//
// Created by fume on 06.03.23.
//

#include <csearch/Test.h>
#include <ranges>
#include <thread>
#include <pqxx/pqxx>

int main() {

    Test::hello();
    try{
        pqxx::connection conn("dbname=iihero hostaddr=127.0.01 user=foo password=foo1");

    } catch (std::exception& e){
        std::cout << "Failed connect to pgsql" << e.what();
    }


    return 0;
}