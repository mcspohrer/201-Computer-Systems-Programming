# Matthew Spohrer
# Prog 3a
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
crcInit:
    xor    %r9, %r9              # set dividend to 0 for first for loop
for1:
    movq   %r9, %rdi             # set remainder equal to dividend
    movq   $8, %rsi              # bit = 8 for nested for loop
for2:
    test   $0x80, %rdi           # if (remainder & 0x80)
    jne    if                    # jump to the if label if test true
    jmp    else                  # jump to else label if test false
if:   
    sal    %rdi                  # shift remainder left once
    xor    $0xD5, %rdi           # shifted remainder ^ POLYNOMIAL
    jmp    endFor1               # skip else part
else:
    sal    %rdi                  # shift remainder left once
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
