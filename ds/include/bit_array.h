#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stddef.h>/*size_t*/

typedef size_t bitarray_t;

typedef enum {
BIT_OFF = 0, 
BIT_ON = 1
} bitstate_t;

/*Description: The function set 'on' the bit in position of bit_index.
@params: The function gets bit_index needs to be between 0 and 63 (included)
 and bitarray.
@return: The function return bitarray_t that bit_index is on.
@errors: No errors.
*/
bitarray_t BitArrSetBitOn(bitarray_t bitarray, size_t bit_index);

/*Description: The function set 'off' the bit in position of bit_index.
@params: The function gets bit_index needs to be between 0 and 63 (included)
and bitarray.
@return: The function returns bitarray_t that bit_index is on.
@errors: No errors.
*/
bitarray_t BitArrSetBitOff(bitarray_t bitarray, size_t bit_index);

/*Description: The function set value to bit in position of bit_index.
@params: The function gets bit_index needs to be between 0 and 63 (included) 
and set_to is '1' for every value unless its '0' and bitarray_t.
@return: The function returns bitarray_t that bit_index is set to set_to.
@errors: No errors.
*/
bitarray_t BitArrSetBit(bitarray_t bitarray, size_t bit_index, int set_to);

/*Description: The function flip value of bit_index.
@params: The function gets bit_index needs to be between 0 and 63 (included) 
and bitarray.
@return: The function returns bitarray_t that bit_index is fliped.
@errors: No errors.
*/
bitarray_t BitArrFlipBit(bitarray_t bitarray, size_t bit_index);

/*Description: check if bit_index is 'on'.
@params: The function gets bit_index needs to be between 0 and 63 (included).
@return: The function returns 1 if the bit_index is on, otherwise return 0.
@errors: No errors.
*/
int BitArrIsBitOn(bitarray_t bitarray, size_t bit_index);

/*Description: check if bit_index is 'off'.
@params: The function gets bit_index needs to be between 0 and 63 (included) 
and bitarray.
@return: The function returns 1 if the bit_index is off, otherwise return 0.
@errors: No errors.
*/
int BitArrIsBitOff(bitarray_t bitarray, size_t bit_index);

/*Description: return the bit_state of bitarray_t.
@params: The function gets bit_index needs to be between 0 and 63 (included)
and bitarray.
@return: The function returns the bit_state (BIT_OFF, BIT_ON)of bitarray_t. 
@errors: No errors.
*/
bitstate_t BitArrGetBit(bitarray_t bitarray, size_t bit_index);

/*Description: count the number of bits that on.
@params: The function gets bitarray of type bittarray_t.
@return: The function returns the number of bits that on.
@errors: No errors.
*/
size_t BitArrCountBitsOn(bitarray_t bitarray);

/*Description: count the number of bits that off.
@params: The function gets bitarray of type bittarray_t.
@return: The function returns the number of bits that off.
@errors: No errors.
*/
size_t BitArrCountBitsOff(bitarray_t bitarray);

/*Description: set 'on' all bits. 
@params: The function gets no params.
@return: The function returns a bitarray that all bits is 'on'.
@errors: No errors.
*/
bitarray_t BitArrSetAll();

/*Description: set 'off' all bits. 
@params: The function gets no params.
@return: The function returns a bitarray that all bits is 'off'.
@errors: No errors.
*/
bitarray_t BitArrUnSetAll();

/*Description: The function will return a mirrored bitarray.
@params: The function gets bitarray of type bitarray_t.   
@return: The function returns a mirrored bitarray of size_t.
@errors: No errors.
*/
bitarray_t BitArrMirror(bitarray_t bitarray);


/*Description: The function will rotate bitarray n times Right.
@params: The function gets bitarray of type bitarray_t and n of size_t. 
@return: The function returns the rotated bitarray of size_t.
@errors: No errors.
*/
bitarray_t BitArrRotateRight(bitarray_t bitarray, size_t n);

/*Description: The function will rotate bitarray n times Left.
@params: The function gets bitarray of type bitarray_t and n of size_t. 
@return: The function returns the rotated bitarray of size_t.
@errors: No errors.
*/
bitarray_t BitArrRotateLeft(bitarray_t bitarray, size_t n);

/*Description: The function will sift bitarray n times Right.
@params: The function gets bitarray of type bitarray_t and n of size_t. 
@return: The function returns the shifted bitarray of size_t.
@errors: No errors.
*/
bitarray_t BitArrShiftRight(bitarray_t bitarray, size_t n);

/*Description: The function will sift bitarray n times Left.
@params: The function gets bitarray of type bitarray_t and n of size_t. 
@return: The function returns the shifted bitarray of size_t.
@errors: No errors.
*/
bitarray_t BitArrShiftLeft(bitarray_t bitarray, size_t n);

/*Description: The function converts the bits content, of bit array into a 
string pointed by buffer.
@params: The function gets bitarray of type bittarray_t and buffer of chars. 
Size of buffer should be greater then 64.  
@return: The function will return the pointer to the beginnig of the string.
@errors: If buffer is not valid, or if it is smaller then target bitarray 
length, this function will produce undefined behavior.
*/
char *BitArrArrToString(bitarray_t bitarray, char *buffer);

#endif /* __BITARRAY_H__ */
