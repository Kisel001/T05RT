;**************************************************************
; Copyright (C) 1992-2024
;    Computer Graphics Support Group of 30 Phys-Math Lyceum
;**************************************************************

; FILE:        strlen.asm
; PROGRAMMER:  IP5
; LAST UPDATE: 30.07.2024
; PURPOSE:     Get string len routine file.
; NOTE:        Work only in x64 mode.
; 
; No part of this file may be changed without agreement of
; Computer Graphics Support Group of 30 Phys-Math Lyceum.

.CODE

; get len of char len (include 0-char) routine.
; ARGUMENTS:
;   - pointer to string
;       CHAR *Str (rcx);
; RETURNS:
;   (size_t, rax) size of str
public StringLen
StringLen \
        proc

        xor     rax, rax                ; in rax we will be save len. set len by zero value.

LenLoop:
        inc     rax                     ; len += 1
        mov     bl, byte ptr [rcx]      ; load char from string
        test    bl, bl                  ; this char is 0?
        jz      FuncEnd                 ; if char is 0, then goto end, else goto next iteration
        inc     rcx                     ; move pointer to next char
        jmp     LenLoop                 ; next iteration 

FuncEnd:
        ret                             ; finally, we counting len, also we leave from routine

StringLen \
        endp
; End of 'StringLen' function

END
; END OF 'strlen.asm' FILE
