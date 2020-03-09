# The LIFE file format info

This implementation of the Game of Life saves files in a .life file format.

The LIFE format packs 8 cells into a single byte, which combined with the simple RLE (Run-length encoding) compression results in at least **4x smaller** files compared to cell data stored in plaintext.

## LIFE file structure

A .life file is divided into 3 sections:

|Section|Size (in bytes)|
|-|-|
|Magic string ("LIFE")|4|
|Width and height|8|
|Compressed board data|*variable*|

### Magic string ("LIFE")

Every LIFE file contains the "LIFE" string at the beginning, which is used for identification. If the file doesn't contain the magic string, the program will not continue reading it.

### Width and height

The dimensions of the GoL board are saved as two `unsigned int`s in the file.

|Dimension|Type|
|-|-|
|Width|`unsigned int`|
|Height|`unsigned int`|

### Compressed board data

GoL board data is saved as a sequence of length-body pairs:

|Item|Type|
|-|-|
|Block length|`char`|
|Block value|`char`|

Each of the pairs corresponds to a sequence of n values equal to the *block value*, with n = *block length*.

For example, if the block length = 3 and block value = 2, the pair corresponds to a sequence `2, 2, 2`.

After "unwrapping" the compressed data (turning each pair into the corresponding sequences), one should end up with an array of `char`s, with the number of items equal to `n`, where:

* If `width * height` is divisible by 8, `n = width*height / 8`,
* If `width * height` is not divisible by 8, `n = width*height / 8 + 1`.

In both cases, the division result is rounded down to an integer.

#### Converting the `char` array to board data

todo