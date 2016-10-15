#include "stdlib.h"
#include "inttypes.h"

char uint6_b64_lookup(uint8_t x) {
    char c;
    if (x < 26) {
        c = 'A'+x;
    }
    else if (x < 52) {
        c = 'a' + (x-26);
    }
    else if (x < 62) {
        c = '0' + (x-52);    
    }
    else {
        switch (x) {
        case 62:    c = '+';    break;
        }
    }
}

uint8_t hex_uint4_lookup(char h) {
    uint8_t i;
    if (h >= '0' && h <= '9') {
        i = h - '0';
    }
    else if (h >= 'a' && h <= 'f') {
        i = 10 + (h-'a');
    }
    else if (h >= 'A' && h <= 'F') {
        i = 10 + (h-'A');
    }
    return i;
}

int hex_uint4_translate(char * h, uint8_t ** ui4p, int len) {
    int ui4_len = len;
    *ui4p = malloc(ui4_len*sizeof(uint8_t));
    if (*ui4p == NULL) { return 0; }

    uint8_t * ui4 = *ui4p;
    for (int idx = 0; idx<ui4_len; idx++) {
        ui4[idx] = hex_uint4_lookup(h[idx]);
    }
    return len;
}

int  uint4_uint6_translate(uint8_t * ui4, uint8_t ** ui6p, int len) {
    int ui6_len = (len<<1)/3;
    *ui6p = malloc(ui6_len*sizeof(uint8_t));
    if (*ui6p == NULL) { return 0 ;}

    uint8_t * ui6 = *ui6p;
    for (int ui4idx = 0, ui6idx = 0; ui6idx<ui6_len, ui4idx<len; ui6idx++) {
        switch(ui6idx%2) {
            case 0:
                ui6[ui6idx] = (ui4[ui4idx]<<2) + (ui4[ui4idx+1]>>2);
                ui4idx+=1;
                break;
            case 1:
                ui6[ui6idx] = ((ui4[ui4idx]&0x3)<<4) + (ui4[ui4idx+1]);
                ui4idx+=2;
                break;
        }
    }
    return ui6_len;
}

int  uint4_uint8_translate(uint8_t * ui4, uint8_t ** ui8p, int len) {
    int ui8_len = (len>>1);
    *ui8p = malloc(ui8_len*sizeof(uint8_t));
    if (*ui8p == NULL) { return 0 ;}

    uint8_t * ui8 = *ui8p;
    for (int ui8idx = 0; ui8idx<ui8_len; ui8idx++) {
        ui8[ui8idx] = (ui4[ui8idx*2]<<4) + (ui4[(ui8idx*2)+1]);
    }
    return ui8_len;
}

int uint6_b64_translate(uint8_t * ui6, char ** b64p, int len) {
    *b64p = malloc(len * sizeof(char));
    if (*b64p == NULL) { return 0; }

    char * b64 = *b64p;
    for (int idx = 0; idx < len; idx++) {
        b64[idx] = uint6_b64_lookup(ui6[idx]);
    }
    return len;
}

int hex_b64_translate(char * h, char ** b64p, int len) {
    uint8_t * ui4, * ui6;
    int ui4len, ui6len, b64len;
    ui4len = hex_uint4_translate(h, &ui4, len);
    if ( ui4len == 0) {
        return 0;
    }
    ui6len = uint4_uint6_translate(ui4, &ui6, len);
    if (ui6len == 0) {
        free(ui4);
        return 0;
    }
    b64len = uint6_b64_translate(ui6, b64p, ui6len);

    free (ui6);
    free(ui4);
    return b64len;
}

