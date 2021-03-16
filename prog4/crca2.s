# Matthew Spohrer
# Prog 4
# Assembly Source Code

# This is the assembly version of the crcInit and crcFast 
# functions supplied to us

    .global crcInit

    .data
POLYNOMIAL:
    .long 0xD5
	.comm	crcTable,256,32

    .text
# dividend == r9
# remainder == rdi
# bit == rsi
# r8 == original remainder
# %rcx == xor'd remainder
crcInit:
    xor    %r9, %r9              # set dividend to 0 for first for loop
for1:
    movq   %r9, %rdi             # set remainder equal to dividend
    movq   $8, %rsi              # bit = 8 for nested for loop
for2:
    movq   %rdi, %r8             # copies remainder to be compared
    sal    %rdi                  # shift remainder left once
    movq   %rdi, %rcx            # copies remainder to be xor'd
    xor    $0xD5, %rcx           # shifted remainder ^ POLYNOMIAL
    test   $0x80, %r8            # if (remainder & 0x80)
    cmovne %rcx, %rdi            # copy xor'd rem back into rdi
endFor1:
    dec    %rsi                  # decrement bit for nested for loop
    cmp    $0, %rsi              # test is bit is > 0
    jg     for2                  # if bit == 0 then exit nested for loop
    leaq   crcTable(%r9), %rdx   # load address of crtTable + dividend into rax
    and    $0xff, %rdi           # and with 0xff mask to get smallest byte
    movq   %rdi, (%rdx)          # move remainder into crt[dividend]
    inc    %r9                   # increment dividend
    cmp    $256, %r9             # checks if dividend < 256
    jl     for1                  # if divdend < 256 then go to for1
    ret                          # exit crcInit
    
    .global crcFast
    .text
# message = rdi
# strlen(message) = rsi
# byte = rdx
# remainder = rcx
# #data = r8
# address of message + byte or crcTable + data = r9
crcFast:
    xor    %rcx, %rcx            # set remainder to zero
    xor    %rdx, %rdx            # set byte to zero
    jmp    testFor
for:
    leaq   (%rdx, %rdi), %r9     # set r9 = address of message[byte]
    movq   %rcx, %r8             # data = remainder for xor  
    xor    (%r9), %r8            # value at message + byte ^ remainder 
    and    $0xff, %r8           
    leaq   crcTable(%r8), %r9    # r9 = crcTable + data
    movq   (%r9), %rcx           # remainder = crcTable[data]
    inc    %rdx                  # ++byte
testFor:
    cmp    %rsi, %rdx            # byte - nByte compare
    jl     for                   # if byte < nByte then continue for
    movq   %rcx, %rax            # else move remainder to rax to be ret
    ret                          # return remainder
