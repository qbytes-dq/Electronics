opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 9453"

opt pagewidth 120

	opt lm

	processor	16F628A
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
# 11 "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\Main.c"
	psect config,class=CONFIG,delta=2 ;#
# 11 "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\Main.c"
	dw 0xFFEE & 0xFFFF & 0xFFBF & 0xFFF7 & 0xFFFB & 0xFF7F & 0xFFFF & 0xFFFF ;#
	FNCALL	_main,_InitUART
	FNCALL	_main,_SendStringSerially
	FNCALL	_main,_ReceiveByteSerially
	FNCALL	_main,_SendByteSerially
	FNCALL	_SendStringSerially,_SendByteSerially
	FNROOT	_main
	FNCALL	_ISR,i1_SendByteSerially
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_chr
	global	_RCREG
psect	text286,local,class=CODE,delta=2
global __ptext286
__ptext286:
_RCREG	set	26
	global	_TXREG
_TXREG	set	25
	global	_CARRY
_CARRY	set	24
	global	_CREN
_CREN	set	196
	global	_GIE
_GIE	set	95
	global	_OERR
_OERR	set	193
	global	_PEIE
_PEIE	set	94
	global	_RA0
_RA0	set	40
	global	_RB7
_RB7	set	55
	global	_RCIF
_RCIF	set	101
	global	_RX9
_RX9	set	198
	global	_SPEN
_SPEN	set	199
	global	_SREN
_SREN	set	197
	global	_TXIF
_TXIF	set	100
	global	_EEADR
_EEADR	set	155
	global	_EECON1
_EECON1	set	156
	global	_EECON2
_EECON2	set	157
	global	_EEDATA
_EEDATA	set	154
	global	_SPBRG
_SPBRG	set	153
	global	_BRGH
_BRGH	set	1218
	global	_RCIE
_RCIE	set	1125
	global	_RD
_RD	set	1248
	global	_SYNC
_SYNC	set	1220
	global	_TRISA0
_TRISA0	set	1064
	global	_TRISB1
_TRISB1	set	1073
	global	_TRISB2
_TRISB2	set	1074
	global	_TRISB7
_TRISB7	set	1079
	global	_TX9
_TX9	set	1222
	global	_TXEN
_TXEN	set	1221
	global	_TXIE
_TXIE	set	1124
	global	_WR
_WR	set	1249
	global	_WREN
_WREN	set	1250
psect	strings,class=STRING,delta=2
global __pstrings
__pstrings:
;	global	stringdir,stringtab,__stringbase
stringtab:
;	String table - string pointers are 1 byte each
stringcode:stringdir:
movlw high(stringdir)
movwf pclath
movf fsr,w
incf fsr
	addwf pc
__stringbase:
	retlw	0
psect	strings
	
STR_1:	
	retlw	72	;'H'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	108	;'l'
	retlw	111	;'o'
	retlw	32	;' '
	retlw	87	;'W'
	retlw	111	;'o'
	retlw	114	;'r'
	retlw	108	;'l'
	retlw	100	;'d'
	retlw	33	;'!'
	retlw	0
psect	strings
	file	"serial-RX-TX.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_chr:
       ds      1

; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	clrf	((__pbssCOMMON)+0)&07Fh
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_SendByteSerially
?_SendByteSerially:	; 0 bytes @ 0x0
	global	?_InitUART
?_InitUART:	; 0 bytes @ 0x0
	global	?_SendStringSerially
?_SendStringSerially:	; 0 bytes @ 0x0
	global	?_ISR
?_ISR:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	?i1_SendByteSerially
?i1_SendByteSerially:	; 0 bytes @ 0x0
	global	??i1_SendByteSerially
??i1_SendByteSerially:	; 0 bytes @ 0x0
	global	?_ReceiveByteSerially
?_ReceiveByteSerially:	; 1 bytes @ 0x0
	global	i1SendByteSerially@Byte
i1SendByteSerially@Byte:	; 1 bytes @ 0x0
	ds	1
	global	??_ISR
??_ISR:	; 0 bytes @ 0x1
	ds	5
	global	??_SendByteSerially
??_SendByteSerially:	; 0 bytes @ 0x6
	global	??_InitUART
??_InitUART:	; 0 bytes @ 0x6
	global	??_ReceiveByteSerially
??_ReceiveByteSerially:	; 0 bytes @ 0x6
	global	SendByteSerially@Byte
SendByteSerially@Byte:	; 1 bytes @ 0x6
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x7
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	??_SendStringSerially
??_SendStringSerially:	; 0 bytes @ 0x0
	ds	1
	global	SendStringSerially@st
SendStringSerially@st:	; 1 bytes @ 0x1
	ds	1
;;Data sizes: Strings 13, constant 0, data 0, bss 1, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      7       8
;; BANK0           80      2       2
;; BANK1           80      0       0
;; BANK2           48      0       0

;;
;; Pointer list with targets:

;; SendStringSerially@st	PTR const unsigned char  size(1) Largest target is 13
;;		 -> STR_1(CODE[13]), 
;;


;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_SendByteSerially
;;   _SendStringSerially->_SendByteSerially
;;
;; Critical Paths under _ISR in COMMON
;;
;;   _ISR->i1_SendByteSerially
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_SendStringSerially
;;
;; Critical Paths under _ISR in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _ISR in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.
;;
;; Critical Paths under _ISR in BANK2
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 0     0      0     109
;;                           _InitUART
;;                 _SendStringSerially
;;                _ReceiveByteSerially
;;                   _SendByteSerially
;; ---------------------------------------------------------------------------------
;; (1) _SendStringSerially                                   2     2      0      87
;;                                              0 BANK0      2     2      0
;;                   _SendByteSerially
;; ---------------------------------------------------------------------------------
;; (1) _ReceiveByteSerially                                  0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _InitUART                                             0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _SendByteSerially                                     1     1      0      22
;;                                              6 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (3) _ISR                                                  5     5      0      73
;;                                              1 COMMON     5     5      0
;;                 i1_SendByteSerially
;; ---------------------------------------------------------------------------------
;; (4) i1_SendByteSerially                                   1     1      0      73
;;                                              0 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 4
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _InitUART
;;   _SendStringSerially
;;     _SendByteSerially
;;   _ReceiveByteSerially
;;   _SendByteSerially
;;
;; _ISR (ROOT)
;;   i1_SendByteSerially
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA              80      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      7       8       1       57.1%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       6       2        0.0%
;;BANK0               50      2       2       3        2.5%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;ABS                  0      0       A       4        0.0%
;;BITBANK0            50      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BITBANK1            50      0       0       6        0.0%
;;BANK1               50      0       0       7        0.0%
;;BITBANK2            30      0       0       8        0.0%
;;BANK2               30      0       0       9        0.0%
;;DATA                 0      0      10      10        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 16 in file "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\Main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_InitUART
;;		_SendStringSerially
;;		_ReceiveByteSerially
;;		_SendByteSerially
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\Main.c"
	line	16
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 4
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	17
	
l2934:	
;Main.c: 17: InitUART();
	fcall	_InitUART
	line	19
	
l2936:	
;Main.c: 19: SendStringSerially("Hello World!");
	movlw	((STR_1-__stringbase))&0ffh
	fcall	_SendStringSerially
	line	21
	
l2938:	
;Main.c: 21: GIE = 1;
	bsf	(95/8),(95)&7
	line	22
	
l2940:	
;Main.c: 22: PEIE = 1;
	bsf	(94/8),(94)&7
	line	24
	
l2942:	
;Main.c: 24: TRISA0=0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1064/8)^080h,(1064)&7
	line	25
	
l2944:	
;Main.c: 25: TRISB7=0;
	bcf	(1079/8)^080h,(1079)&7
	line	26
	
l2946:	
;Main.c: 26: RA0=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(40/8),(40)&7
	line	27
	
l2948:	
;Main.c: 27: RB7=0;
	bcf	(55/8),(55)&7
	goto	l2950
	line	28
;Main.c: 28: while(1)
	
l768:	
	line	33
	
l2950:	
;Main.c: 29: {
;Main.c: 33: SendByteSerially(ReceiveByteSerially());
	fcall	_ReceiveByteSerially
	fcall	_SendByteSerially
	goto	l2950
	line	34
	
l769:	
	line	28
	goto	l2950
	
l770:	
	line	35
	
l771:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_SendStringSerially
psect	text287,local,class=CODE,delta=2
global __ptext287
__ptext287:

;; *************** function _SendStringSerially *****************
;; Defined at:
;;		line 50 in file "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
;; Parameters:    Size  Location     Type
;;  st              1    wreg     PTR const unsigned char 
;;		 -> STR_1(13), 
;; Auto vars:     Size  Location     Type
;;  st              1    1[BANK0 ] PTR const unsigned char 
;;		 -> STR_1(13), 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       1       0       0
;;      Temps:          0       1       0       0
;;      Totals:         0       2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_SendByteSerially
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text287
	file	"C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
	line	50
	global	__size_of_SendStringSerially
	__size_of_SendStringSerially	equ	__end_of_SendStringSerially-_SendStringSerially
	
_SendStringSerially:	
	opt	stack 4
; Regs used in _SendStringSerially: [wreg-fsr0h+status,2+status,0+pclath+cstack]
;SendStringSerially@st stored from wreg
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(SendStringSerially@st)
	line	51
	
l2926:	
;UART.c: 51: while(*st)
	goto	l2932
	
l1165:	
	line	52
	
l2928:	
;UART.c: 52: SendByteSerially(*st++);
	movf	(SendStringSerially@st),w
	movwf	fsr0
	fcall	stringdir
	fcall	_SendByteSerially
	
l2930:	
	movlw	(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_SendStringSerially+0)+0
	movf	(??_SendStringSerially+0)+0,w
	addwf	(SendStringSerially@st),f
	goto	l2932
	
l1164:	
	line	51
	
l2932:	
	movf	(SendStringSerially@st),w
	movwf	fsr0
	fcall	stringdir
	iorlw	0
	skipz
	goto	u2351
	goto	u2350
u2351:
	goto	l2928
u2350:
	goto	l1167
	
l1166:	
	line	53
	
l1167:	
	return
	opt stack 0
GLOBAL	__end_of_SendStringSerially
	__end_of_SendStringSerially:
;; =============== function _SendStringSerially ends ============

	signat	_SendStringSerially,4216
	global	_ReceiveByteSerially
psect	text288,local,class=CODE,delta=2
global __ptext288
__ptext288:

;; *************** function _ReceiveByteSerially *****************
;; Defined at:
;;		line 34 in file "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text288
	file	"C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
	line	34
	global	__size_of_ReceiveByteSerially
	__size_of_ReceiveByteSerially	equ	__end_of_ReceiveByteSerially-_ReceiveByteSerially
	
_ReceiveByteSerially:	
	opt	stack 5
; Regs used in _ReceiveByteSerially: [wreg]
	line	37
	
l1980:	
;UART.c: 37: if(OERR)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(193/8),(193)&7
	goto	u41
	goto	u40
u41:
	goto	l1158
u40:
	line	39
	
l1982:	
;UART.c: 38: {
;UART.c: 39: CREN = 0;
	bcf	(196/8),(196)&7
	line	40
;UART.c: 40: CREN = 1;
	bsf	(196/8),(196)&7
	goto	l1158
	line	41
	
l1157:	
	line	43
;UART.c: 41: }
;UART.c: 43: while(!RCIF);
	goto	l1158
	
l1159:	
	
l1158:	
	btfss	(101/8),(101)&7
	goto	u51
	goto	u50
u51:
	goto	l1158
u50:
	goto	l1984
	
l1160:	
	line	46
	
l1984:	
;UART.c: 46: return RCREG;
	movf	(26),w	;volatile
	goto	l1161
	
l1986:	
	line	47
	
l1161:	
	return
	opt stack 0
GLOBAL	__end_of_ReceiveByteSerially
	__end_of_ReceiveByteSerially:
;; =============== function _ReceiveByteSerially ends ============

	signat	_ReceiveByteSerially,89
	global	_InitUART
psect	text289,local,class=CODE,delta=2
global __ptext289
__ptext289:

;; *************** function _InitUART *****************
;; Defined at:
;;		line 8 in file "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text289
	file	"C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
	line	8
	global	__size_of_InitUART
	__size_of_InitUART	equ	__end_of_InitUART-_InitUART
	
_InitUART:	
	opt	stack 5
; Regs used in _InitUART: [wreg]
	line	9
	
l1954:	
;UART.c: 9: TRISB2 = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1074/8)^080h,(1074)&7
	line	10
;UART.c: 10: TRISB1 = 1;
	bsf	(1073/8)^080h,(1073)&7
	line	12
	
l1956:	
;UART.c: 12: SPBRG = ((20000000/16)/9600) - 1;
	movlw	(081h)
	movwf	(153)^080h	;volatile
	line	13
	
l1958:	
;UART.c: 13: BRGH = 1;
	bsf	(1218/8)^080h,(1218)&7
	line	14
	
l1960:	
;UART.c: 14: SYNC = 0;
	bcf	(1220/8)^080h,(1220)&7
	line	15
	
l1962:	
;UART.c: 15: SPEN = 1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(199/8),(199)&7
	line	16
	
l1964:	
;UART.c: 16: CREN = 1;
	bsf	(196/8),(196)&7
	line	17
	
l1966:	
;UART.c: 17: SREN = 0;
	bcf	(197/8),(197)&7
	line	18
	
l1968:	
;UART.c: 18: TXIE = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1124/8)^080h,(1124)&7
	line	19
	
l1970:	
;UART.c: 19: RCIE = 1;
	bsf	(1125/8)^080h,(1125)&7
	line	20
	
l1972:	
;UART.c: 20: TX9 = 0;
	bcf	(1222/8)^080h,(1222)&7
	line	21
	
l1974:	
;UART.c: 21: RX9 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(198/8),(198)&7
	line	22
	
l1976:	
;UART.c: 22: TXEN = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1221/8)^080h,(1221)&7
	line	23
	
l1978:	
;UART.c: 23: TXEN = 1;
	bsf	(1221/8)^080h,(1221)&7
	line	24
	
l1148:	
	return
	opt stack 0
GLOBAL	__end_of_InitUART
	__end_of_InitUART:
;; =============== function _InitUART ends ============

	signat	_InitUART,88
	global	_SendByteSerially
psect	text290,local,class=CODE,delta=2
global __ptext290
__ptext290:

;; *************** function _SendByteSerially *****************
;; Defined at:
;;		line 28 in file "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
;; Parameters:    Size  Location     Type
;;  Byte            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Byte            1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         1       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         1       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;;		_SendStringSerially
;; This function uses a non-reentrant model
;;
psect	text290
	file	"C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
	line	28
	global	__size_of_SendByteSerially
	__size_of_SendByteSerially	equ	__end_of_SendByteSerially-_SendByteSerially
	
_SendByteSerially:	
	opt	stack 5
; Regs used in _SendByteSerially: [wreg]
;SendByteSerially@Byte stored from wreg
	movwf	(SendByteSerially@Byte)
	line	29
	
l2892:	
;UART.c: 29: while(!TXIF);
	goto	l1151
	
l1152:	
	
l1151:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(100/8),(100)&7
	goto	u2321
	goto	u2320
u2321:
	goto	l1151
u2320:
	goto	l2894
	
l1153:	
	line	30
	
l2894:	
;UART.c: 30: TXREG = Byte;
	movf	(SendByteSerially@Byte),w
	movwf	(25)	;volatile
	line	31
	
l1154:	
	return
	opt stack 0
GLOBAL	__end_of_SendByteSerially
	__end_of_SendByteSerially:
;; =============== function _SendByteSerially ends ============

	signat	_SendByteSerially,4216
	global	_ISR
psect	text291,local,class=CODE,delta=2
global __ptext291
__ptext291:

;; *************** function _ISR *****************
;; Defined at:
;;		line 7 in file "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\ISR.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          5       0       0       0
;;      Totals:         5       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		i1_SendByteSerially
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text291
	file	"C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\ISR.c"
	line	7
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 4
; Regs used in _ISR: [wreg+status,2+status,0+pclath+cstack]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_ISR+1)
	movf	fsr0,w
	movwf	(??_ISR+2)
	movf	pclath,w
	movwf	(??_ISR+3)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	btemp+1,w
	movwf	(??_ISR+4)
	ljmp	_ISR
psect	text291
	line	8
	
i1l2880:	
;ISR.c: 8: if(RCIF)
	btfss	(101/8),(101)&7
	goto	u230_21
	goto	u230_20
u230_21:
	goto	i1l383
u230_20:
	line	10
	
i1l2882:	
;ISR.c: 9: {
;ISR.c: 10: RA0=1;
	bsf	(40/8),(40)&7
	line	11
;ISR.c: 11: if(OERR)
	btfss	(193/8),(193)&7
	goto	u231_21
	goto	u231_20
u231_21:
	goto	i1l382
u231_20:
	line	13
	
i1l2884:	
;ISR.c: 12: {
;ISR.c: 13: CREN = 0;
	bcf	(196/8),(196)&7
	line	14
;ISR.c: 14: CREN = 1;
	bsf	(196/8),(196)&7
	line	15
	
i1l382:	
	line	16
;ISR.c: 15: }
;ISR.c: 16: RA0=0;
	bcf	(40/8),(40)&7
	line	17
;ISR.c: 17: RB7=1;
	bsf	(55/8),(55)&7
	line	18
	
i1l2886:	
;ISR.c: 18: chr=RCREG;
	movf	(26),w	;volatile
	movwf	(??_ISR+0)+0
	movf	(??_ISR+0)+0,w
	movwf	(_chr)
	line	20
	
i1l2888:	
;ISR.c: 20: SendByteSerially(chr);
	movf	(_chr),w
	fcall	i1_SendByteSerially
	line	21
	
i1l2890:	
;ISR.c: 21: RB7=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(55/8),(55)&7
	goto	i1l383
	line	22
	
i1l381:	
	line	23
	
i1l383:	
	movf	(??_ISR+4),w
	movwf	btemp+1
	movf	(??_ISR+3),w
	movwf	pclath
	movf	(??_ISR+2),w
	movwf	fsr0
	swapf	(??_ISR+1)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_ISR
	__end_of_ISR:
;; =============== function _ISR ends ============

	signat	_ISR,88
	global	i1_SendByteSerially
psect	text292,local,class=CODE,delta=2
global __ptext292
__ptext292:

;; *************** function i1_SendByteSerially *****************
;; Defined at:
;;		line 28 in file "C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
;; Parameters:    Size  Location     Type
;;  SendByteSeri    1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  SendByteSeri    1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         1       0       0       0
;;      Temps:          0       0       0       0
;;      Totals:         1       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_ISR
;; This function uses a non-reentrant model
;;
psect	text292
	file	"C:\Users\davidq\Documents\GitHub\electronics\Serial com - 16F628A\UART.c"
	line	28
	global	__size_ofi1_SendByteSerially
	__size_ofi1_SendByteSerially	equ	__end_ofi1_SendByteSerially-i1_SendByteSerially
	
i1_SendByteSerially:	
	opt	stack 4
; Regs used in i1_SendByteSerially: [wreg]
;i1SendByteSerially@Byte stored from wreg
	movwf	(i1SendByteSerially@Byte)
	line	29
	
i1l2896:	
;UART.c: 29: while(!TXIF);
	goto	i1l1151
	
i1l1152:	
	
i1l1151:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(100/8),(100)&7
	goto	u233_21
	goto	u233_20
u233_21:
	goto	i1l1151
u233_20:
	goto	i1l2898
	
i1l1153:	
	line	30
	
i1l2898:	
;UART.c: 30: TXREG = Byte;
	movf	(i1SendByteSerially@Byte),w
	movwf	(25)	;volatile
	line	31
	
i1l1154:	
	return
	opt stack 0
GLOBAL	__end_ofi1_SendByteSerially
	__end_ofi1_SendByteSerially:
;; =============== function i1_SendByteSerially ends ============

	signat	i1_SendByteSerially,88
psect	text293,local,class=CODE,delta=2
global __ptext293
__ptext293:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
