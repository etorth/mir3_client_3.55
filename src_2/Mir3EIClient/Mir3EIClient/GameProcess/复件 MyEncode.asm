 .386P
 .model FLAT
; externdef _snd_scaletable:dword 定义外部变量
;ml $(InputPath) /c /Cp /coff /Fo$(OUTDIR)\$(InputName).obj /Zm /Zi  

_TEXT SEGMENT
public _sub_42f760

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






_TEXT ENDS
END