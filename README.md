# Proprietary Assembler (PASM)

An implementation of a simple yet fast two-pass assembler in C with tries for fast in-memory opcode fetch.

## Supports

* Parsing assembler scripts
* Generation of intermediate file
* Generation of object file
* Generation of symbol tables
* Loader creating exe files





### Instructions on running

Write the source assembly in a source file such as `file.pasm` and then run the following command:

```
$make test

```

The above command takes care of assembling the source code, linking and executing the binary.


## Limitations

* The [opcodes.csv](./opcodes.csv) file contains the supported opcodes, more opcodes has to be supported and some have yet undefined lenghts.
* There is no support for macros
* There is no support for some assembler directives such as `EXTERN` , `ORG` and `LTORG`.
* There is yet no support for multiple control sections.
