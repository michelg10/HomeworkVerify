#ifndef aes_h
#define aes_h
#include <bits/stdc++.h>
#include "aes_lookup.h"
using namespace std;
typedef long long ll;
void aes_keyCore (unsigned char *in, unsigned char i) {
    unsigned int* q=(unsigned int*)in;
    *q=(*q>>8)|((*q&0xff)<<24); //rotate
    for (ll i=0;i<4;i++) in[i]=sbox[in[i]]; //sbox
    in[0]^=rcon[i]; //rcon
}
void aes_keyExpand(unsigned char *inKey, unsigned char * expKey, ll keySz) {
    ll sksz,coreSch;
    if (keySz==176) {
        sksz=16;
        coreSch=16;
    } else if (keySz==208) {
        sksz=24;
        coreSch=24;
    } else if (keySz==240) {
        sksz=32;
        coreSch=32;
    } else return;
    for (ll i=0;i<sksz;i++) expKey[i]=inKey[i];
    ll bytesGen=sksz;
    ll rconItr=1;
    unsigned char tmp[4];
    while (bytesGen<keySz) {
        for (ll i=0;i<4;i++) tmp[i]=expKey[i+bytesGen-4]; //EK((r-1)*4)
        if (bytesGen%coreSch==0) {
            aes_keyCore(tmp,rconItr++);
        }
        if (bytesGen%32==16&&keySz==240) {
            for (ll i=0;i<4;i++) tmp[i]=sbox[tmp[i]];
        }
        for (ll i=0;i<4;i++) {
            expKey[bytesGen]=expKey[bytesGen-sksz]^tmp[i]; //xor it with last result EK((r-4)*4)
            bytesGen++;
        }
    }
}
void aes_subBytes(unsigned char* state) {
    for (ll i=0;i<16;i++) {
        state[i]=sbox[state[i]];
    }
}
void aes_inv_subBytes(unsigned char* state) {
    for (ll i=0;i<16;i++) {
        state[i]=inv_sbox[state[i]];
    }
}
void aes_shiftRows(unsigned char* state) {
    unsigned char tmp[16];
    for (ll i=0;i<=3;i++) {
        for (ll j=i;j<=15;j+=4) {
            tmp[j]=state[(j+4*i)%16];
        }
    }
    for (ll i=0;i<16;i++) state[i]=tmp[i];
}
void aes_inv_shiftRows(unsigned char* state) {
    unsigned char tmp[16];
    for (ll i=0;i<=3;i++) {
        for (ll j=i;j<=15;j+=4) {
            tmp[j]=state[(j-4*i+16)%16];
        }
    }
    for (ll i=0;i<16;i++) state[i]=tmp[i];
}
void aes_mixColumns(unsigned char* state) {
    unsigned char tmp[16];
    for (ll i=0;i<15;i+=4) {
        tmp[i]=(unsigned char)(mul2[state[i]] ^ mul3[state[i+1]] ^ state[i+2] ^ state[i+3]);
        tmp[i+1] = (unsigned char)(state[i] ^ mul2[state[i+1]] ^ mul3[state[i+2]] ^ state[i+3]);
        tmp[i+2] = (unsigned char)(state[i] ^ state[i+1] ^ mul2[state[i+2]] ^ mul3[state[i+3]]);
        tmp[i+3] = (unsigned char)(mul3[state[i]] ^ state[i+1] ^ state[i+2] ^ mul2[state[i+3]]);
    }
    for (ll i=0;i<16;i++) state[i]=tmp[i];
}
void aes_inv_mixColumns(unsigned char* state) {
    unsigned char tmp[16];
    for (ll i=0;i<15;i+=4) {
        tmp[i]=(unsigned char)(mul14[state[i]] ^ mul11[state[i+1]] ^ mul13[state[i+2]] ^ mul9[state[i+3]]);
        tmp[i+1] = (unsigned char)(mul9[state[i]] ^ mul14[state[i+1]] ^ mul11[state[i+2]] ^ mul13[state[i+3]]);
        tmp[i+2] = (unsigned char)(mul13[state[i]] ^ mul9[state[i+1]] ^ mul14[state[i+2]] ^ mul11[state[i+3]]);
        tmp[i+3] = (unsigned char)(mul11[state[i]] ^ mul13[state[i+1]] ^ mul9[state[i+2]] ^ mul14[state[i+3]]);
    }
    for (ll i=0;i<16;i++) state[i]=tmp[i];
}
void aes_addRndKey(unsigned char* state, unsigned char* rndkey) {
    for (ll i=0;i<16;i++) state[i]^=rndkey[i];
}
void aes_encrypt_raw(unsigned char* message, unsigned char* expKey,ll rounds) {
    unsigned char state[16];
    for (ll i=0;i<16;i++) {
        state[i]=message[i];
    }
    
    aes_addRndKey(state,expKey);
    for (ll i=1;i<rounds;i++) {
        aes_subBytes(state);
        aes_shiftRows(state);
        aes_mixColumns(state);
        aes_addRndKey(state,expKey+(16*i));
    }
    aes_subBytes(state);
    aes_shiftRows(state);
    aes_addRndKey(state,expKey+16*rounds);
    for (ll i=0;i<16;i++) message[i]=state[i];
}
void aes_encrypt(unsigned char* message,ll messageLen, unsigned char* key,ll keyLen,unsigned char* iv) {
    ll keysz,rndamt;
    if (keyLen==16) {
        keysz=176;
        rndamt=10;
    } else if (keyLen==24) {
        keysz=208;
        rndamt=12;
    } else if (keyLen==32) {
        keysz=240;
        rndamt=14;
    } else {
        cout<<"Error! Key size must be 128, 192, or 256 bits!"<<endl;
        return;
    }
    unsigned char expKey[keysz];
    aes_keyExpand(key,expKey,keysz);
    for (ll i=0;i<16;i++) message[i]^=iv[i];
    aes_encrypt_raw(message,expKey,rndamt);
    for (ll i=16;i<messageLen;i+=16) {
        for (ll j=i;j<i+16;j++) message[j]^=message[j-16];
        aes_encrypt_raw(message+i,expKey,rndamt);
    }
}
void aes_decrypt_raw(unsigned char* message, unsigned char* expKey,ll rounds) {
    unsigned char state[16];
    for (ll i=0;i<16;i++) {
        state[i]=message[i];
    }
    
    aes_addRndKey(state,expKey+16*rounds);
    for (ll i=1;i<rounds;i++) {
        aes_inv_shiftRows(state);
        aes_inv_subBytes(state);
        aes_addRndKey(state,expKey+(16*rounds-16*i));
        aes_inv_mixColumns(state);
    }
    aes_inv_shiftRows(state);
    aes_inv_subBytes(state);
    aes_addRndKey(state,expKey);
    for (ll i=0;i<16;i++) message[i]=state[i];
}
void aes_decrypt(unsigned char* message,ll messageLen, unsigned char* key,ll keyLen, unsigned char* iv) {
    ll keysz,rndamt;
    if (keyLen==16) {
        keysz=176;
        rndamt=10;
    } else if (keyLen==24) {
        keysz=208;
        rndamt=12;
    } else if (keyLen==32) {
        keysz=240;
        rndamt=14;
    } else {
        cout<<"Error! Key size must be 128, 192, or 256 bits!"<<endl;
        return;
    }
    unsigned char expKey[keysz];
    aes_keyExpand(key,expKey,keysz);
    for (ll i=messageLen-16;i>=16;i-=16) {
        aes_decrypt_raw(message+i,expKey,rndamt);
        for (ll j=i;j<i+16;j++) message[j]^=message[j-16];
    }
    aes_decrypt_raw(message,expKey,rndamt);
    for (ll i=0;i<16;i++) message[i]^=iv[i];
}
#endif /* aes_h */
