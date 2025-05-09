;**************************************************************
; Copyright (C) 1992-2024
;    Computer Graphics Support Group of 30 Phys-Math Lyceum
;**************************************************************

; FILE:        memtools.asm
; PROGRAMMER:  IP5
; LAST UPDATE: 23.07.2024
; PURPOSE:     Work with memory routines file.
; NOTE:        Work only in x64 mode.
; 
; No part of this file may be changed without agreement of
; Computer Graphics Support Group of 30 Phys-Math Lyceum.

.CODE

; Fill memory by dword value routine.
; ARGUMENTS:
;   - destination:
;       void *dest (rcx);
;   - value:
;       dword value (edx);
;   - count:
;       size_t count (r8);
; RETURNS: 
;   (void *) destination (rax).
public DMemset
DMemset \
        proc

        push    rdi

        mov     r11, rcx                ; save destination
        mov     rdi, rcx                ; set destination
        mov     rcx, r8                 ; set count
        mov     eax, edx                ; set value
        rep     stosd                   ; store dwords
        mov     rax, r11                ; set return value (destination)

        pop     rdi

        ret

DMemset \
        endp
; End of 'DMemset' routine.

; Fill memory by zero value routine.
; ARGUMENTS:
;   - destination:
;       void *dest (rcx);
;   - count:
;       size_t count (rdx);
; RETURNS: 
;   (void *) destination (rax).
public FillZero
FillZero \
        proc

        push    rdi

        mov     r11, rcx                ; save destination
        mov     rdi, rcx                ; set destination
        mov     rcx, rdx                ; set count
        xor     eax, eax                ; set value by 0
        rep     stosd                   ; store dwords
        mov     rax, r11                ; set return value (destination)

        pop     rdi

        ret

FillZero \
        endp
; End of 'DMemset' routine.

; Fill memory by word value routine.
; ARGUMENTS:
;   - destination:
;       void *dest (rcx);
;   - value:
;       word value (dx);
;   - count:
;       size_t count (r8);
; RETURNS: 
;   (void *) destination (rax).
public WMemset
WMemset \
        proc

        push    rdi

        mov     r11, rcx                ; save destination
        mov     rdi, rcx                ; set destination
        mov     rcx, r8                 ; set count
        mov     ax,  dx                 ; set value
        rep     stosw                   ; store words
        mov     rax, r11                ; set return value (destination)

        pop     rdi

        ret

WMemset \
        endp
; End of 'WMemset' routine.

; Fill memory by qword value routine.
; ARGUMENTS:
;   - destination:
;       void *dest (rcx);
;   - value:
;       qword value (rdx);
;   - count:
;       size_t count (r8);
; RETURNS: 
;   (void *) destination (rax).
public QMemset
QMemset \
        proc

        push    rdi

        mov     r11, rcx                ; save destination
        mov     rdi, rcx                ; set destination
        mov     rcx, r8                 ; set count
        mov     rax, rdx                ; set value
        rep     stosq                   ; store qwords
        mov     rax, r11                ; set return value (destination)

        pop     rdi

        ret

QMemset \
        endp
; End of 'QMemset' routine.

END

; END OF 'memtools.asm' FILE
