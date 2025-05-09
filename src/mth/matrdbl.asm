;**************************************************************
; Copyright (C) 1992-2024
;    Computer Graphics Support Group of 30 Phys-Math Lyceum
;**************************************************************

; FILE:        matrdbl.asm
; PROGRAMMER:  IP5
; LAST UPDATE: 23.07.2024
; PURPOSE:     Work with double matrix routines file.
; NOTE:        Work only in x64 mode.
; 
; No part of this file may be changed without agreement of
; Computer Graphics Support Group of 30 Phys-Math Lyceum.

.CODE

; matr mul matr for double routine.
; ARGUMENTS:
;   - dest:
;       float *mdst;
;   - src1:
;       const float *msrc1;
;   - src2:
;       const float *msrc2;
; RETURNS: None.
public MatrMulMatr
MatrMulMatr \
        proc

        vmovupd         ymm3, ymmword ptr [r8]
        vmovupd         ymm4, ymmword ptr [r8+20h]  
        vmovupd         ymm5, ymmword ptr [r8+40h]  
        vmovupd         ymm15, ymmword ptr [r8+60h]  
        vbroadcastsd    ymm0, mmword ptr [rdx]  
        vmulpd          ymm2, ymm3, ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+8]  
        vfmadd231pd     ymm2,ymm0,ymm4  
        vbroadcastsd    ymm0,mmword ptr [rdx+10h]  
        vmulpd          ymm1,ymm5,ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+18h]  
        vfmadd231pd     ymm1,ymm0,ymm15  
        vaddpd          ymm0,ymm1,ymm2  
        vmovupd         ymmword ptr [rcx],ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+20h]  
        vmulpd          ymm2,ymm3,ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+28h]  
        vfmadd231pd     ymm2,ymm0,ymm4  
        vbroadcastsd    ymm0,mmword ptr [rdx+30h]  
        vmulpd          ymm1,ymm5,ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+38h]  
        vfmadd231pd     ymm1,ymm0,ymm15  
        vaddpd          ymm0,ymm1,ymm2  
        vmovupd         ymmword ptr [rcx+20h],ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+40h]  
        vmulpd          ymm2,ymm3,ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+48h]  
        vfmadd231pd     ymm2,ymm0,ymm4  
        vbroadcastsd    ymm0,mmword ptr [rdx+50h]  
        vmulpd          ymm1,ymm5,ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+58h]  
        vfmadd231pd     ymm1,ymm0,ymm15  
        vaddpd          ymm0,ymm1,ymm2  
        vmovupd         ymmword ptr [rcx+40h],ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+60h]  
        vmulpd          ymm2,ymm3,ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+68h]  
        vfmadd231pd     ymm2,ymm0,ymm4  
        vbroadcastsd    ymm0,mmword ptr [rdx+70h]  
        vmulpd          ymm1,ymm5,ymm0  
        vbroadcastsd    ymm0,mmword ptr [rdx+78h]  
        vfmadd231pd     ymm1,ymm0,ymm15  
        vaddpd          ymm0,ymm1,ymm2  
        vmovupd         ymmword ptr [rcx+60h],ymm0  
        vzeroupper  

        ret

MatrMulMatr \
        endp
; End of 'MatrMulMatr' routine

END
; END OF 'matrdbl.asm' FILE
