//
// Created by 2022 on 4/25/2024.
//

#ifndef FINAL_PROJECT_EXCEPTIONS_H
#define FINAL_PROJECT_EXCEPTIONS_H

#include <exception>
#include <iostream>

using namespace std;

class Exceptions :public exception{
    string Emessage;
public:
    explicit Exceptions(const string& Emessage);
    Exceptions(const Exceptions& rhs);
    Exceptions& operator=(const Exceptions& rhs);
    ~Exceptions() override;
    Exceptions(Exceptions&& rhs) noexcept ;
    Exceptions& operator=(Exceptions&& rhs) noexcept ;
    const char* what() const noexcept override;
};


#endif //FINAL_PROJECT_EXCEPTIONS_H
