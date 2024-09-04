//
// Created by 2022 on 4/25/2024.
//

#include "Exceptions.h"

const char *Exceptions::what() const noexcept  {
    return Emessage.c_str();
}

Exceptions::Exceptions(const string &Emessage):Emessage(Emessage) {

}

Exceptions::Exceptions(const Exceptions &rhs):Emessage(rhs.Emessage) {

}



Exceptions &Exceptions::operator=(const Exceptions &rhs) {
    if(this==&rhs)
        return *this;
    Emessage=rhs.Emessage;
    return *this;
}

Exceptions::Exceptions(Exceptions &&rhs) noexcept:Emessage(move(rhs.Emessage)) {

}

Exceptions &Exceptions::operator=(Exceptions&& rhs) noexcept {
    if (this == &rhs)
        return *this;
    Emessage = move(rhs.Emessage);
    return *this;
}

Exceptions::~Exceptions() = default;
