#include "factorization.h"

bool Factorization::simple_is_prime(unsigned long long num){
    if(num==2||num==3||num==5) return true;
    unsigned long long i = 2;
    unsigned long long limit = num;
    if(0==num%i++) return false;
    while(num%i){
        if(i<limit){
            limit = num/i;
            i += 2;
        }
        else
            return true;
    }
    return false;
}
void Factorization::set_simple_prime_list(unsigned long long num){
    simple_prime_list.push_back(2);
    simple_prime_list.push_back(3);
    for(unsigned long long i = 5;i<=num;i=i+2)
        if(simple_is_prime(i))
            simple_prime_list.push_back(i);
}
unsigned long long Factorization::simple_primes_factorial(unsigned long long num){
    unsigned long long num_out = 1;
    if(num<=simple_prime_list.back())
        for(unsigned long long i=0;i<simple_prime_list.size();i++){
            if(simple_prime_list[i]>num) break;
            num_out = num_out*simple_prime_list[i];
        }
    return num_out;
}
void Factorization::set_base_list(){
    size_base = temp_size_base;
    temp_size_base = 0;
    unsigned long long * temp_list = base_list;
    base_list = temp_base_list;
    temp_base_list = temp_list;
    for(unsigned long long i = 0;i<size_base;i++)
        if(base_list[i]%simple_prime_list[simple_primes_number_index])
            temp_base_list[temp_size_base++] = base_list[i];
}
void Factorization::set_primes_list(){
    if(size_primes==0){
        for(unsigned long long i=0;simple_prime_list[i]<add_factor;i++)
            primes_list[size_primes++] = simple_prime_list[i];
        if(add_factor==6&&temp_size_base==0){
            temp_base_list[temp_size_base++] = 1;
            temp_base_list[temp_size_base++] = 5;
        }
        set_base_list();
        set_primes_list();
    }
    else{
        bool is_prime = true;
        unsigned long long candidate = 0;
        while(true){
            for(unsigned long long i=1;i<simple_prime_list[simple_primes_number_index];i++){
                unsigned long long temp_add_factor = add_factor*i;
                for(unsigned long long j=0;j<size_base;j++){
                    candidate = base_list[j] + temp_add_factor;
                    for(unsigned long long ip=0;primes_list[ip]<add_factor;ip++)
                        if(candidate%primes_list[ip]==0){
                            is_prime = false;
                            break;
                        }
                    if(candidate>simple_prime_list[simple_primes_number_index])
                        if(candidate%simple_prime_list[simple_primes_number_index])
                            temp_base_list[temp_size_base++] = candidate;
                    if(is_prime){
                        primes_list[size_primes++] = candidate;
                        if(size_primes%10000==0) std::cout<<"%";
                    }
                    is_prime = true;
                }
            }
            add_factor *= simple_prime_list[simple_primes_number_index];
            set_base_list();
            if(add_factor>=max_add_factor) return;
            simple_primes_number_index++;
        }
    }
}
void Factorization::print_primes(){
    std::cout<<"\n";
    for(unsigned i=0;i<size_primes;i++){
        if(i%10==0) std::cout<<"\n";
        std::cout<<"\t"<<primes_list[i];
    }
}
unsigned long long Factorization::get_last_prime(){
    return primes_list[size_primes-1];
}
unsigned long long Factorization::get_size_primes(){
    return size_primes;
}
unsigned long long Factorization::get_size_base(){
    return size_base;
}
void Factorization::print_base(){
    std::cout<<"\n";
    for(unsigned i=0;i<size_base;i++){
        if(i%10==0) std::cout<<"\n";
        std::cout<<"\t"<<base_list[i];
    }
}
void Factorization::factors(unsigned long long num){
    list_of_factors = find_factors(num);
    std::cout<<"\nList_of_factors of "<<num<<" :";
    for(unsigned i = 0;i<list_of_factors.size();i++)
        std::cout<<"\n\t[ "<<list_of_factors[i]<<" ]";
}
std::vector<unsigned long long> Factorization::find_factors(unsigned long long num){
    unsigned long long limit = (unsigned long long)sqrt((long double)num);
    unsigned long long index = 0;
    std::vector<unsigned long long> list_to_return;
    while(true){
        if(num%simple_prime_list[index])
            if(index<simple_primes_number_index)
                index++;
            else break;
        else {
            list_to_return = find_factors(num/simple_prime_list[index]);
            list_to_return.push_back(simple_prime_list[index]);
            return list_to_return;
        }
    }
    unsigned long long Nloops = 1 + limit/max_add_factor;
    unsigned long long loc_add_factor = 0;
    for(unsigned long long i = 0; i<Nloops;i++){
        loc_add_factor = max_add_factor*i;
        for(unsigned long long j = 0; j<size_base;j++)
            if(num%(base_list[j]+loc_add_factor)==0){
                if((base_list[j]+loc_add_factor)>1){
                    list_to_return = find_factors(num/(base_list[j]+loc_add_factor));
                    list_to_return.push_back(base_list[j]+loc_add_factor);
                    return list_to_return;
                }
            }
    }
    list_to_return.push_back(num);
    return list_to_return;
}
