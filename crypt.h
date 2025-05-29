//
//  crypt.h
//  idk
//
//  Created by evan matthews on 22/5/2025.
//

#ifndef crypt_h
typedef unsigned short uint16_t;

enum which_algorithem{
    SHA_512 = 1,
    SHA_384,
    SHA_256
    
};



struct crypt_items{
        uint16_t random;
        char string[100];
        enum which_algorithem which;
        char output[200];
};
#endif/*        crypt_h        */
