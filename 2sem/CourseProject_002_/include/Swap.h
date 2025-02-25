#ifndef SWAP_HPP_
#define SWAP_HPP_

#define SWAP(name, type)                                \
void swap_##name(type *a, type *b) {                    \
    type temp = *a;                                     \
    *a = *b;                                            \
    *b = temp;                                          \
}

#endif