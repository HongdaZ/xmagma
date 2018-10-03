/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: hzhang
 *
 * Created on July 10, 2018, 9:49 AM
 */

#include <stdlib.h>
#include <iostream>
#include <matrix.h>
/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "newsimpletest test 1" << std::endl;
}

void test2() {
    std::cout << "newsimpletest test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    Sales_item book;
    
    std::cout << book.avg_price() << std::endl;
    return (EXIT_SUCCESS);
}

