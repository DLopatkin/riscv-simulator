//
// Created by harld on 29-Apr-18.
//

#include "context.h"


Hart::Hart(){
    this->PC = 0;
    this->regfile = {0};
    this->regfile[2] = 0x1000000 - 8;
}

