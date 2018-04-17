#include <stdlib.h>

size_t cgc_receive_fixed(void *buf, size_t size){
  *(size_t *)buf = size;
  return size;
}

void * cgc_calloc(unsigned int size, int val){
  return calloc(size, val);
}

void cgc_free(void*ptr){ free(ptr); }

int cgc_ReceiveCommand1() {
    int decoded_size;
    char *decoded_data;
    size_t bytes_received;

    bytes_received = cgc_receive_fixed((char *)&decoded_size, sizeof(decoded_size));
    if (bytes_received != sizeof(decoded_size)) {
      return -1;
    }
    decoded_data = cgc_calloc(decoded_size + 1, 1);
    cgc_free(decoded_data);
    return 0;
}

int cgc_ReceiveCommand2() {
    int encoded_size;
    int decoded_size;
    char *decoded_data;
    size_t bytes_received;

    bytes_received = cgc_receive_fixed((char *)&encoded_size, sizeof(encoded_size));
    if (bytes_received != sizeof(encoded_size)) {
      return -1;
    }
    decoded_size = (encoded_size * 8) / 7;
    decoded_data = cgc_calloc(decoded_size + 1, 1);
    cgc_free(decoded_data);
    return 0;
}

int cgc_ReceiveCommand3() {
    int encoded_size;
    int decoded_size;
    int useless_interloper;
    char *decoded_data;
    size_t bytes_received;

    bytes_received = cgc_receive_fixed((char *)&encoded_size, sizeof(encoded_size));
    if (bytes_received != sizeof(encoded_size)) {
      return -1;
    }
    useless_interloper = encoded_size;
    decoded_size = (useless_interloper * 8) / 7;
    decoded_data = cgc_calloc(decoded_size + 1, 1);
    cgc_free(decoded_data);
    return 0;
}

void * calloc_wrapper(int size, int value){
  return cgc_calloc(size, value);
}

int cgc_ReceiveCommand4() {
    int decoded_size;
    char *decoded_data;
    size_t bytes_received;

    bytes_received = cgc_receive_fixed((char *)&decoded_size, sizeof(decoded_size));
    if (bytes_received != sizeof(decoded_size)) {
      return -1;
    }
    decoded_data = calloc_wrapper(decoded_size + 1, 1);
    cgc_free(decoded_data);
    return 0;
}

