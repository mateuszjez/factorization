#ifndef FACTORIZATION_H
#define FACTORIZATION_H
#include <iostream>
#include <vector>
#include <thread>
#include <math.h>
class Factorization
{
public:
    Factorization(unsigned long long num = 17) {
        set_simple_prime_list(num);
        max_add_factor = simple_primes_factorial(num);
        primes_list = new unsigned long long[max_add_factor/3];
        base_list = new unsigned long long[max_add_factor/2];
        temp_base_list = new unsigned long long[max_add_factor/2];
        temp_base_list[0] = 1;
        temp_base_list[1] = 5;
        temp_size_base = 2;
        unsigned long long tempfact = (max_add_factor/3);
        for(unsigned long long i=0;i<tempfact;i++){
            primes_list[i] = LONG_LONG_MAX;
            base_list[i] = LONG_LONG_MAX;
        }
        set_primes_list();
        ///dynamic assignment of threads:
        number_of_cores = std::thread::hardware_concurrency();
        thX = new std::thread*[number_of_cores];
        returnX = new uslong[number_of_cores];
        for(unsigned int i=0; i<number_of_cores; ++i)
            returnX[i] = 0;
        base_parts_bounds = new uslong[number_of_cores+1];
        base_parts_bounds[0] = 0;
        for(unsigned int i=1; i<=number_of_cores; ++i)
        {
            base_parts_bounds[i] = base_parts_bounds[i-1] + size_base/number_of_cores;
        }
        base_parts_bounds[number_of_cores] = size_base;
    }
    ~Factorization() {
        delete temp_base_list;
        delete base_list;
        delete primes_list;
    }
    void print_primes();
    unsigned long long get_last_prime();
    unsigned long long get_size_primes();
    unsigned long long get_size_base();
    void print_base();
    void factors(unsigned long long num);
    std::vector<unsigned long long>  find_factors(unsigned long long num);
    unsigned long long              find_next_factor(unsigned long long num);
    std::vector<unsigned long long>  list_of_factors;
private:
    std::vector<unsigned long long> simple_prime_list;
    bool simple_is_prime(unsigned long long num);
    void set_simple_prime_list(unsigned long long num);
    unsigned long long simple_primes_factorial(unsigned long long num);
    unsigned simple_primes_number_index = 2;//initial value
    unsigned long long * primes_list;
    void set_primes_list();
    unsigned long long size_primes = 0;
    unsigned long long * base_list;
    unsigned long long * temp_base_list;
    unsigned long long add_factor = 6;//first two primes product (2*3)
    void set_base_list();
    unsigned long long size_base = 0;
    unsigned long long temp_size_base = 0;
    unsigned long long max_add_factor;
    unsigned int number_of_cores;
    std::thread ** thX;
    unsigned long long * returnX;
    unsigned long long * base_parts_bounds;
};

#endif // FACTORIZATION_H
