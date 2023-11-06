# mycpu is freely redistributable under the MIT License. See the file                                                                                        
# "LICENSE" for information on usage and redistribution of this file.

.global _start
_start:
    li a0, 0x80000000
    lw t0, 4(a0)
    li a1, 0xBEEF
    sw a1, 4(a0)
    nop
    lw t1, 4(a0)
loop:
    j loop
