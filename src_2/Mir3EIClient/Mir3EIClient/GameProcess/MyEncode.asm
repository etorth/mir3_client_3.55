 .386P
 .model FLAT
; externdef _snd_scaletable:dword 定义外部变量
;ml $(InputPath) /c /Cp /coff /Fo$(OUTDIR)\$(InputName).obj /Zm /Zi  

_DATA SEGMENT

dword_4B8658    dd 227F1675h            
                dd 9875h, 9873h

                
_DATA ENDS  

_TEXT SEGMENT
public _sub_42f760

public _sub_430230
public _sub_42F6B0
public _sub_47D330

;void _SetWord(DWORD dw)
_SetWord proc near
arg_0		= dword	ptr  8
	mov eax, [esp+arg_0]
	mov dword_4B8658, eax
	ret
_SetWord	endp	


_sub_42F760	proc near		
var_1		= dword	ptr -1
arg_0		= dword	ptr  7

		push	ecx
		mov	edx, [esp+1+arg_0]
		push	ebx
		push	edi
		mov	edi, edx
		or	ecx, 0FFFFFFFFh
		xor	eax, eax
		xor	ebx, ebx
		repne scasb
		not	ecx
		dec	ecx
		cmp	ecx, 14h
		jnb	short loc_42F783
		pop	edi
		xor	ax, ax
		pop	ebx
		pop	ecx
;		retn	4
		ret

loc_42F783:				; CODE XREF: sub_42F760+18
		push	ebp
		push	esi
		xor	esi, esi
		inc	edx

loc_42F788:				; CODE XREF: sub_42F760+72
		mov	al, [edx-1]
		mov	cl, [edx+8]
		mov	byte ptr [esp+11h+var_1], al
		mov	byte ptr [esp+11h+arg_0], cl
		mov	ecx, [esp+11h+arg_0]
		mov	edi, [esp+11h+var_1]
		and	ecx, 0FFh
		and	edi, 0FFh
		xor	eax, eax
		add	edi, ecx

loc_42F7AE:				; CODE XREF: sub_42F760+67
		xor	ecx, ecx
		mov	cl, [edx+eax]
		cmp	ecx, edi
		jl	short loc_42F7C3
		lea	ecx, [esi+eax]
		mov	ebp, 8000h
		sar	ebp, cl
		or	ebx, ebp

loc_42F7C3:				; CODE XREF: sub_42F760+55
		inc	eax
		cmp	eax, 7
		jle	short loc_42F7AE
		add	esi, 8
		add	edx, 0Ah
		cmp	esi, 8
		jle	short loc_42F788
		xor	eax, eax
		pop	esi
		mov	al, bh
		and	ebx, 0FFh
		and	eax, 0FFh
		xor	ebx, 87h
		xor	eax, 87h
		pop	ebp
		shl	ebx, 8
		or	eax, ebx
		pop	edi
		pop	ebx
		pop	ecx
;		retn	4
		ret
_sub_42F760	endp

;***********************************************************************************
;函数 sub_42F6B0	esp+4
;extern "C" void _sub_42F6B0(char* pszData)

_sub_42F6B0      proc near               
var_1           = dword ptr -1
arg_0           = dword ptr  7

                push    ecx
                mov     edx, [esp+1+arg_0]
                push    ebx
                push    edi
                mov     edi, edx
                or      ecx, 0FFFFFFFFh
                xor     eax, eax
                xor     ebx, ebx
                repne scasb
                not     ecx
                dec     ecx
                cmp     ecx, 28h
                jnb     short loc_42F6D0
                pop     edi
                pop     ebx
                pop     ecx
         ;       retn    4
				ret

loc_42F6D0:                             ; CODE XREF: sub_42F6B0+18j
                push    ebp
                push    esi
                xor     esi, esi
                inc     edx

loc_42F6D5:                             ; CODE XREF: sub_42F6B0+6Fj
                mov     al, [edx-1]
                mov     cl, [edx+8]
                mov     byte ptr [esp+11h+var_1], al
                mov     byte ptr [esp+11h+arg_0], cl
                mov     ecx, [esp+11h+arg_0]
                mov     edi, [esp+11h+var_1]
                and     ecx, 0FFh
                and     edi, 0FFh
                xor     eax, eax
                add     edi, ecx

loc_42F6FB:                             ; CODE XREF: sub_42F6B0+64j
                xor     ecx, ecx
                mov     cl, [edx+eax]
                cmp     ecx, edi
                jl      short loc_42F710
                lea     ecx, [esi+eax]
                mov     ebp, 80000000h
                shr     ebp, cl
                or      ebx, ebp

loc_42F710:                             ; CODE XREF: sub_42F6B0+52j
                inc     eax
                cmp     eax, 7
                jle     short loc_42F6FB
                add     esi, 8
                add     edx, 0Ah
                cmp     esi, 18h
                jbe     short loc_42F6D5
                mov     dl, bl
                mov     eax, ebx
                xor     dl, 87h
                xor     ecx, ecx
                shr     eax, 10h
                mov     ch, dl
                mov     dl, al
                mov     cl, bh
                xor     dl, 87h
                xor     ebx, ebx
                pop     esi
                mov     bh, dl
                xor     edx, edx
                shl     ecx, 10h
                and     ebx, 0FFFFh
                mov     dl, ah
                or      ecx, ebx
                and     edx, 0FFh
                or      ecx, edx
                pop     ebp
                pop     edi
                mov     eax, ecx
                pop     ebx
                pop     ecx
          ;      retn    4
				ret     
_sub_42F6B0      endp



;***********************************************************************************
;函数sub_430230		esp+8
;extern "C" void sub_430230(short* pShort, char* pszData)

_sub_430230      proc near               

var_C           = dword ptr -0Ch
var_8           = dword ptr -8
var_4           = dword ptr -4
arg_0           = dword ptr  4
arg_4           = dword ptr  8

                sub     esp, 0Ch
                mov     eax, [esp+0Ch+arg_4] ; var_2B8
                push    ebx
                push    ebp
                push    esi
                push    edi
                lea     edi, [eax+1]
                mov     [esp+1Ch+var_C], 4

loc_430246:               
                mov     ecx, [esp+1Ch+arg_0]
                push    31h
                push    0
                mov     dl, [ecx]
                xor     dl, 87h
                mov     byte ptr [esp+24h+var_8], dl
                call    sub_401710
                mov     ebx, eax
                push    13h
                push    0
                add     bl, 0Ah
                call    sub_401710
                add     al, 0Ah
                mov     [edi-1], bl
                mov     byte ptr [esp+2Ch+arg_4], al
                mov     [edi+8], al
                mov     eax, [esp+2Ch+var_8]
                mov     ebp, [esp+2Ch+arg_4]
                add     esp, 10h
                xor     esi, esi
                and     eax, 0FFh
                mov     [esp+1Ch+var_4], eax
                jmp     short loc_430292


loc_43028E:                             
                mov     eax, [esp+1Ch+var_4]

loc_430292:                             
                mov     edx, 80h
                mov     ecx, esi
                sar     edx, cl
                test    eax, edx
                jnz     short loc_4302B4
                mov     eax, ebp
                and     eax, 0FFh
                dec     eax
                push    eax
                push    0
                call    sub_401710
                add     esp, 8
                jmp     short loc_4302CE


loc_4302B4:                            
                mov     ecx, ebp
                and     ecx, 0FFh
                dec     ecx
                push    ecx
                push    0
                call    sub_401710
                mov     dl, byte ptr [esp+24h+arg_4]
                add     esp, 8
                add     al, dl

loc_4302CE:                            
                add     al, bl
                mov     [edi+esi], al
                inc     esi
                cmp     esi, 8
                jl      short loc_43028E
                mov     edx, [esp+1Ch+arg_0]
                mov     eax, [esp+1Ch+var_C]
                inc     edx
                add     edi, 0Ah
                dec     eax
                mov     [esp+1Ch+arg_0], edx
                mov     [esp+1Ch+var_C], eax
                jnz     loc_430246
                pop     edi
                pop     esi
                pop     ebp
                pop     ebx
                add     esp, 0Ch
            ;    retn    8
				ret
_sub_430230      endp



;**************************************************************************
;;函数sub_401710
sub_401710      proc near               

arg_0           = dword ptr  0Ch
arg_4           = dword ptr  10h

                push    esi
                push    edi
                call    sub_49FDAE
                mov     esi, eax
                call    sub_49FDAE
                sub     esi, eax
                jns     short loc_401724
                neg     esi

loc_401724:                             ; CODE XREF: sub_401710+10j
                mov     edi, [esp+arg_4]
                mov     ecx, [esp+arg_0]
                mov     eax, esi
                sub     edi, ecx
                cdq
                inc     edi
                idiv    edi
                pop     edi
                pop     esi
                mov     eax, edx
                add     eax, ecx
                retn
sub_401710      endp


;*****************************************************************

sub_49FDAE      proc near               

                mov     eax, ds:dword_4B8658
                imul    eax, 343FDh
                add     eax, 269EC3h
                mov     ds:dword_4B8658, eax
                sar     eax, 10h
                and     eax, 7FFFh
                retn
sub_49FDAE      endp

;***************************************************************
;函数 sub_47D330	esp+4
;extern "C" void _sub_47D330(char* pszData)

_sub_47D330      proc near              

arg_0           = dword ptr  0Ch

                push    esi
                push    edi
                mov     esi, ecx
                push    0
                push    0
                push    0
                lea     edi, [esi+18h]
                push    0
                push    47Eh
                push    edi
                call    sub_47D8B0      ; 关注这个地方是否加密的地方
                mov     eax, [esp+arg_0]
;                push    0
;                push    eax
;                push    edi
;                mov     ecx, esi
;                call    SendPacket
                pop     edi
                pop     esi
        ;        retn    4
				ret
_sub_47D330      endp

;********************************************************************************

sub_47D8B0      proc near               ; CODE XREF: sub_47BBE0+36p
                                        ; sub_47BC30+38p ...

arg_0           = dword ptr  4
arg_4           = word ptr  8
arg_8           = dword ptr  0Ch
arg_C           = word ptr  10h
arg_10          = word ptr  14h
arg_14          = word ptr  18h

                mov     eax, [esp+arg_0]
                mov     cx, [esp+arg_4]
                mov     edx, [esp+arg_8]
                mov     [eax+4], cx
                mov     cx, [esp+arg_C]
                mov     [eax], edx
                mov     dx, [esp+arg_10]
                mov     [eax+6], cx
                mov     cx, [esp+arg_14]
                mov     [eax+8], dx
                mov     [eax+0Ah], cx
                retn    18h
sub_47D8B0      endp



_TEXT ENDS
END