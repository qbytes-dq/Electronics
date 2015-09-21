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
# 25 "C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
	psect config,class=CONFIG,delta=2 ;#
# 25 "C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
	dw 0x3FFB & 0x3FFF & 0x3F7F & 0x3FFD ;#
	FNCALL	_main,_init
	FNCALL	_main,___lldiv
	FNCALL	_main,___llmod
	FNCALL	_main,_clear
	FNCALL	_main,_display
	FNCALL	_main,_clock
	FNCALL	_display,_clock
	FNCALL	_clear,_clock
	FNCALL	_init,_clock
	FNROOT	_main
	global	_d1
	global	_d2
	global	_d3
	global	_d4
	global	_d5
	global	_d6
	global	_d7
	global	_period
	global	_CMCON
psect	text206,local,class=CODE,delta=2
global __ptext206
__ptext206:
_CMCON	set	31
	global	_PORTA
_PORTA	set	5
	global	_PORTB
_PORTB	set	6
	global	_T1CON
_T1CON	set	16
	global	_TMR0
_TMR0	set	1
	global	_TMR1H
_TMR1H	set	15
	global	_TMR1L
_TMR1L	set	14
	global	_CARRY
_CARRY	set	24
	global	_GIE
_GIE	set	95
	global	_RA0
_RA0	set	40
	global	_RA1
_RA1	set	41
	global	_RB0
_RB0	set	48
	global	_RB7
_RB7	set	55
	global	_T0IF
_T0IF	set	90
	global	_TMR1IF
_TMR1IF	set	96
	global	_TMR1ON
_TMR1ON	set	128
	global	_EEADR
_EEADR	set	155
	global	_EECON1
_EECON1	set	156
	global	_EECON2
_EECON2	set	157
	global	_EEDATA
_EEDATA	set	154
	global	_OPTION
_OPTION	set	129
	global	_TRISA
_TRISA	set	133
	global	_TRISB
_TRISB	set	134
	global	_RD
_RD	set	1248
	global	_WR
_WR	set	1249
	global	_WREN
_WREN	set	1250
	file	"FrequencyCounterLCD.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_d1:
       ds      1

_d2:
       ds      1

_d3:
       ds      1

_d4:
       ds      1

_d5:
       ds      1

_d6:
       ds      1

_d7:
       ds      1

_period:
       ds      1

; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	clrf	((__pbssBANK0)+0)&07Fh
	clrf	((__pbssBANK0)+1)&07Fh
	clrf	((__pbssBANK0)+2)&07Fh
	clrf	((__pbssBANK0)+3)&07Fh
	clrf	((__pbssBANK0)+4)&07Fh
	clrf	((__pbssBANK0)+5)&07Fh
	clrf	((__pbssBANK0)+6)&07Fh
	clrf	((__pbssBANK0)+7)&07Fh
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_clock
?_clock:	; 0 bytes @ 0x0
	global	??_clock
??_clock:	; 0 bytes @ 0x0
	global	?_clear
?_clear:	; 0 bytes @ 0x0
	global	??_clear
??_clear:	; 0 bytes @ 0x0
	global	?_display
?_display:	; 0 bytes @ 0x0
	global	??_display
??_display:	; 0 bytes @ 0x0
	global	?_init
?_init:	; 0 bytes @ 0x0
	global	??_init
??_init:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	?___lldiv
?___lldiv:	; 4 bytes @ 0x0
	global	___lldiv@divisor
___lldiv@divisor:	; 4 bytes @ 0x0
	ds	1
	global	display@fig
display@fig:	; 1 bytes @ 0x1
	ds	3
	global	___lldiv@dividend
___lldiv@dividend:	; 4 bytes @ 0x4
	ds	4
	global	??___lldiv
??___lldiv:	; 0 bytes @ 0x8
	ds	1
	global	___lldiv@quotient
___lldiv@quotient:	; 4 bytes @ 0x9
	ds	4
	global	___lldiv@counter
___lldiv@counter:	; 1 bytes @ 0xD
	ds	1
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	?___llmod
?___llmod:	; 4 bytes @ 0x0
	global	___llmod@divisor
___llmod@divisor:	; 4 bytes @ 0x0
	ds	4
	global	___llmod@dividend
___llmod@dividend:	; 4 bytes @ 0x4
	ds	4
	global	??___llmod
??___llmod:	; 0 bytes @ 0x8
	ds	1
	global	___llmod@counter
___llmod@counter:	; 1 bytes @ 0x9
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0xA
	ds	4
	global	main@freq2
main@freq2:	; 2 bytes @ 0xE
	ds	2
	global	main@freq1
main@freq1:	; 1 bytes @ 0x10
	ds	1
	global	main@nz
main@nz:	; 1 bytes @ 0x11
	ds	1
	global	main@total
main@total:	; 4 bytes @ 0x12
	ds	4
;;Data sizes: Strings 0, constant 0, data 0, bss 8, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14     14      14
;; BANK0           80     22      30
;; BANK1           80      0       0
;; BANK2           48      0       0

;;
;; Pointer list with targets:

;; ?___llmod	unsigned long  size(1) Largest target is 4
;;		 -> main@total(BANK0[4]), 
;;
;; ?___lldiv	unsigned long  size(1) Largest target is 0
;;


;;
;; Critical Paths under _main in COMMON
;;
;;   _main->___lldiv
;;   ___llmod->___lldiv
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->___llmod
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 4, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                12    12      0     930
;;                                             10 BANK0     12    12      0
;;                               _init
;;                            ___lldiv
;;                            ___llmod
;;                              _clear
;;                            _display
;;                              _clock
;; ---------------------------------------------------------------------------------
;; (1) _display                                              2     2      0      44
;;                                              0 COMMON     2     2      0
;;                              _clock
;; ---------------------------------------------------------------------------------
;; (1) _clear                                                1     1      0       0
;;                                              0 COMMON     1     1      0
;;                              _clock
;; ---------------------------------------------------------------------------------
;; (1) _init                                                 2     2      0       0
;;                                              0 COMMON     2     2      0
;;                              _clock
;; ---------------------------------------------------------------------------------
;; (1) _clock                                                0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) ___lldiv                                             14     6      8     162
;;                                              0 COMMON    14     6      8
;; ---------------------------------------------------------------------------------
;; (1) ___llmod                                             10     2      8     159
;;                                              0 BANK0     10     2      8
;;                            ___lldiv (ARG)
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _init
;;     _clock
;;   ___lldiv
;;   ___llmod
;;     ___lldiv (ARG)
;;   _clear
;;     _clock
;;   _display
;;     _clock
;;   _clock
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA              80      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      E       E       1      100.0%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       2       2        0.0%
;;BANK0               50     16      1E       3       37.5%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;ABS                  0      0      2C       4        0.0%
;;BITBANK0            50      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BITBANK1            50      0       0       6        0.0%
;;BANK1               50      0       0       7        0.0%
;;BITBANK2            30      0       0       8        0.0%
;;BANK2               30      0       0       9        0.0%
;;DATA                 0      0      2E      10        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 53 in file "C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  total           4   18[BANK0 ] unsigned long 
;;  freq2           2   14[BANK0 ] unsigned int 
;;  nz              1   17[BANK0 ] unsigned char 
;;  freq1           1   16[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       8       0       0
;;      Temps:          0       4       0       0
;;      Totals:         0      12       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_init
;;		___lldiv
;;		___llmod
;;		_clear
;;		_display
;;		_clock
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
	line	53
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	57
	
l2814:	
;FrequencyCounterLCD.c: 54: unsigned long total;
;FrequencyCounterLCD.c: 55: unsigned int freq2;
;FrequencyCounterLCD.c: 56: unsigned char freq1,nz;
;FrequencyCounterLCD.c: 57: init();
	fcall	_init
	goto	l2816
	line	58
;FrequencyCounterLCD.c: 58: for(;;){
	
l352:	
	line	59
	
l2816:	
;FrequencyCounterLCD.c: 59: freq1 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@freq1)
	line	60
	
l2818:	
;FrequencyCounterLCD.c: 60: freq2 = 0;
	clrf	(main@freq2)
	clrf	(main@freq2+1)
	line	61
	
l2820:	
;FrequencyCounterLCD.c: 61: TMR1L = 0;
	clrf	(14)	;volatile
	line	62
	
l2822:	
;FrequencyCounterLCD.c: 62: TMR1H = 0;
	clrf	(15)	;volatile
	line	63
	
l2824:	
;FrequencyCounterLCD.c: 63: TMR1IF = 0;
	bcf	(96/8),(96)&7
	line	64
	
l2826:	
;FrequencyCounterLCD.c: 64: nz=0;
	clrf	(main@nz)
	line	65
	
l2828:	
;FrequencyCounterLCD.c: 65: TMR1ON = 1;
	bsf	(128/8),(128)&7
	line	66
	
l2830:	
;FrequencyCounterLCD.c: 66: TMR0 = 0;
	clrf	(1)	;volatile
	line	67
	
l2832:	
;FrequencyCounterLCD.c: 67: T0IF=0;
	bcf	(90/8),(90)&7
	line	69
;FrequencyCounterLCD.c: 69: while (!TMR1IF){
	goto	l2838
	
l354:	
	line	70
;FrequencyCounterLCD.c: 70: if (T0IF){++freq2; T0IF=0;}
	btfss	(90/8),(90)&7
	goto	u2551
	goto	u2550
u2551:
	goto	l2838
u2550:
	
l2834:	
	movlw	low(01h)
	addwf	(main@freq2),f
	skipnc
	incf	(main@freq2+1),f
	movlw	high(01h)
	addwf	(main@freq2+1),f
	
l2836:	
	bcf	(90/8),(90)&7
	goto	l2838
	
l355:	
	goto	l2838
	line	71
	
l353:	
	line	69
	
l2838:	
	btfss	(96/8),(96)&7
	goto	u2561
	goto	u2560
u2561:
	goto	l354
u2560:
	goto	l2840
	
l356:	
	line	73
	
l2840:	
;FrequencyCounterLCD.c: 71: }
;FrequencyCounterLCD.c: 73: freq1=TMR0;
	movf	(1),w	;volatile
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@freq1)
	line	74
	
l2842:	
;FrequencyCounterLCD.c: 74: TMR1ON = 0;
	bcf	(128/8),(128)&7
	line	76
	
l2844:	
;FrequencyCounterLCD.c: 76: total=(unsigned long)freq1 + (unsigned long)freq2 * 256;
	movf	(main@freq2),w
	movwf	((??_main+0)+0)
	movf	(main@freq2+1),w
	movwf	((??_main+0)+0+1)
	clrf	((??_main+0)+0+2)
	clrf	((??_main+0)+0+3)
	movlw	08h
u2575:
	clrc
	rlf	(??_main+0)+0,f
	rlf	(??_main+0)+1,f
	rlf	(??_main+0)+2,f
	rlf	(??_main+0)+3,f
u2570:
	addlw	-1
	skipz
	goto	u2575
	movf	(main@freq1),w
	addwf	0+(??_main+0)+0,w
	movwf	(main@total)
	movf	1+(??_main+0)+0,w
	skipnc
	incfsz	1+(??_main+0)+0,w
	clrc
	movwf	((main@total))+1
	
	movf	2+(??_main+0)+0,w
	skipnc
	incfsz	2+(??_main+0)+0,w
	clrc
	movwf	((main@total))+2
	
	movf	3+(??_main+0)+0,w
	skipnc
	incf	3+(??_main+0)+0,w
	movwf	((main@total))+3
	line	77
	
l2846:	
;FrequencyCounterLCD.c: 77: d7=total/1000000+48;
	movlw	0
	movwf	(?___lldiv+3)
	movlw	0Fh
	movwf	(?___lldiv+2)
	movlw	042h
	movwf	(?___lldiv+1)
	movlw	040h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	0+(((0+(?___lldiv)))),w
	addlw	030h
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d7)
	line	78
	
l2848:	
;FrequencyCounterLCD.c: 78: d6=(total/100000) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	01h
	movwf	(?___lldiv+2)
	movlw	086h
	movwf	(?___lldiv+1)
	movlw	0A0h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d6)
	line	79
	
l2850:	
;FrequencyCounterLCD.c: 79: d5=(total/10000) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	027h
	movwf	(?___lldiv+1)
	movlw	010h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d5)
	line	80
	
l2852:	
;FrequencyCounterLCD.c: 80: d4=(total/1000) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	03h
	movwf	(?___lldiv+1)
	movlw	0E8h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d4)
	line	81
	
l2854:	
;FrequencyCounterLCD.c: 81: d3=(total/100) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	0
	movwf	(?___lldiv+1)
	movlw	064h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d3)
	line	82
	
l2856:	
;FrequencyCounterLCD.c: 82: d2=(total/10) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	0
	movwf	(?___lldiv+1)
	movlw	0Ah
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d2)
	line	83
	
l2858:	
;FrequencyCounterLCD.c: 83: d1=total %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movf	(main@total+3),w
	movwf	3+(?___llmod)+04h
	movf	(main@total+2),w
	movwf	2+(?___llmod)+04h
	movf	(main@total+1),w
	movwf	1+(?___llmod)+04h
	movf	(main@total),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d1)
	line	84
	
l2860:	
;FrequencyCounterLCD.c: 84: clear();
	fcall	_clear
	line	86
	
l2862:	
;FrequencyCounterLCD.c: 86: display(32);
	movlw	(020h)
	fcall	_display
	line	87
	
l2864:	
;FrequencyCounterLCD.c: 87: display(32);
	movlw	(020h)
	fcall	_display
	line	89
	
l2866:	
;FrequencyCounterLCD.c: 89: if(d7 == 48){display(32); display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d7),w
	xorlw	030h
	skipz
	goto	u2581
	goto	u2580
u2581:
	goto	l2870
u2580:
	
l2868:	
	movlw	(020h)
	fcall	_display
	movlw	(020h)
	fcall	_display
	goto	l2874
	line	90
	
l357:	
	
l2870:	
;FrequencyCounterLCD.c: 90: else{display(d7); display(44); nz=1;}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d7),w
	fcall	_display
	movlw	(02Ch)
	fcall	_display
	
l2872:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@nz)
	bsf	status,0
	rlf	(main@nz),f
	goto	l2874
	
l358:	
	line	91
	
l2874:	
;FrequencyCounterLCD.c: 91: if(d6 == 48 && nz==0){display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d6),w
	xorlw	030h
	skipz
	goto	u2591
	goto	u2590
u2591:
	goto	l2880
u2590:
	
l2876:	
	movf	(main@nz),f
	skipz
	goto	u2601
	goto	u2600
u2601:
	goto	l2880
u2600:
	
l2878:	
	movlw	(020h)
	fcall	_display
	goto	l2884
	line	92
	
l359:	
	
l2880:	
;FrequencyCounterLCD.c: 92: else{display(d6); nz=1;}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d6),w
	fcall	_display
	
l2882:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@nz)
	bsf	status,0
	rlf	(main@nz),f
	goto	l2884
	
l360:	
	line	93
	
l2884:	
;FrequencyCounterLCD.c: 93: if(d5 == 48 && nz==0){display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d5),w
	xorlw	030h
	skipz
	goto	u2611
	goto	u2610
u2611:
	goto	l2890
u2610:
	
l2886:	
	movf	(main@nz),f
	skipz
	goto	u2621
	goto	u2620
u2621:
	goto	l2890
u2620:
	
l2888:	
	movlw	(020h)
	fcall	_display
	goto	l2894
	line	94
	
l361:	
	
l2890:	
;FrequencyCounterLCD.c: 94: else{display(d5); nz=1;}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d5),w
	fcall	_display
	
l2892:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@nz)
	bsf	status,0
	rlf	(main@nz),f
	goto	l2894
	
l362:	
	line	95
	
l2894:	
;FrequencyCounterLCD.c: 95: if(d4 == 48 && nz==0){display(32); display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d4),w
	xorlw	030h
	skipz
	goto	u2631
	goto	u2630
u2631:
	goto	l2900
u2630:
	
l2896:	
	movf	(main@nz),f
	skipz
	goto	u2641
	goto	u2640
u2641:
	goto	l2900
u2640:
	
l2898:	
	movlw	(020h)
	fcall	_display
	movlw	(020h)
	fcall	_display
	goto	l364
	line	96
	
l363:	
	
l2900:	
;FrequencyCounterLCD.c: 96: else{display(d4); display(44);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d4),w
	fcall	_display
	movlw	(02Ch)
	fcall	_display
	
l364:	
	line	98
;FrequencyCounterLCD.c: 98: display(d3);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d3),w
	fcall	_display
	line	99
;FrequencyCounterLCD.c: 99: display(d2);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d2),w
	fcall	_display
	line	100
;FrequencyCounterLCD.c: 100: display(d1);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d1),w
	fcall	_display
	line	101
;FrequencyCounterLCD.c: 101: display(32);
	movlw	(020h)
	fcall	_display
	line	102
;FrequencyCounterLCD.c: 102: display(72);
	movlw	(048h)
	fcall	_display
	line	103
;FrequencyCounterLCD.c: 103: display(122);
	movlw	(07Ah)
	fcall	_display
	line	106
	
l2902:	
;FrequencyCounterLCD.c: 106: PORTB=12; clock(); PORTB=0; clock();
	movlw	(0Ch)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	fcall	_clock
	
l2904:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(6)	;volatile
	
l2906:	
	fcall	_clock
	line	107
	
l2908:	
;FrequencyCounterLCD.c: 107: _delay((unsigned long)((2)*(400000/4000.0)));
	opt asmopt_off
movlw	66
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
movwf	(??_main+0)+0,f
u2737:
decfsz	(??_main+0)+0,f
	goto	u2737
	clrwdt
opt asmopt_on

	line	109
	
l2910:	
;FrequencyCounterLCD.c: 109: nz=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@nz)
	line	110
	
l2912:	
;FrequencyCounterLCD.c: 110: if(total<1000){total=1000000/total; period=117;}
	movlw	0
	subwf	(main@total+3),w
	skipz
	goto	u2655
	movlw	0
	subwf	(main@total+2),w
	skipz
	goto	u2655
	movlw	03h
	subwf	(main@total+1),w
	skipz
	goto	u2655
	movlw	0E8h
	subwf	(main@total),w
u2655:
	skipnc
	goto	u2651
	goto	u2650
u2651:
	goto	l2918
u2650:
	
l2914:	
	movf	(main@total+3),w
	movwf	(?___lldiv+3)
	movf	(main@total+2),w
	movwf	(?___lldiv+2)
	movf	(main@total+1),w
	movwf	(?___lldiv+1)
	movf	(main@total),w
	movwf	(?___lldiv)

	movlw	0
	movwf	3+(?___lldiv)+04h
	movlw	0Fh
	movwf	2+(?___lldiv)+04h
	movlw	042h
	movwf	1+(?___lldiv)+04h
	movlw	040h
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(main@total+3)
	movf	(2+(?___lldiv)),w
	movwf	(main@total+2)
	movf	(1+(?___lldiv)),w
	movwf	(main@total+1)
	movf	(0+(?___lldiv)),w
	movwf	(main@total)

	
l2916:	
	movlw	(075h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_period)
	goto	l2922
	line	111
	
l365:	
	
l2918:	
;FrequencyCounterLCD.c: 111: else{total=1000000000/total; period=110;}
	movf	(main@total+3),w
	movwf	(?___lldiv+3)
	movf	(main@total+2),w
	movwf	(?___lldiv+2)
	movf	(main@total+1),w
	movwf	(?___lldiv+1)
	movf	(main@total),w
	movwf	(?___lldiv)

	movlw	03Bh
	movwf	3+(?___lldiv)+04h
	movlw	09Ah
	movwf	2+(?___lldiv)+04h
	movlw	0CAh
	movwf	1+(?___lldiv)+04h
	movlw	0
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(main@total+3)
	movf	(2+(?___lldiv)),w
	movwf	(main@total+2)
	movf	(1+(?___lldiv)),w
	movwf	(main@total+1)
	movf	(0+(?___lldiv)),w
	movwf	(main@total)

	
l2920:	
	movlw	(06Eh)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_period)
	goto	l2922
	
l366:	
	line	113
	
l2922:	
;FrequencyCounterLCD.c: 113: d7=total/1000000+48;
	movlw	0
	movwf	(?___lldiv+3)
	movlw	0Fh
	movwf	(?___lldiv+2)
	movlw	042h
	movwf	(?___lldiv+1)
	movlw	040h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	0+(((0+(?___lldiv)))),w
	addlw	030h
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d7)
	line	114
	
l2924:	
;FrequencyCounterLCD.c: 114: d6=(total/100000) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	01h
	movwf	(?___lldiv+2)
	movlw	086h
	movwf	(?___lldiv+1)
	movlw	0A0h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d6)
	line	115
	
l2926:	
;FrequencyCounterLCD.c: 115: d5=(total/10000) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	027h
	movwf	(?___lldiv+1)
	movlw	010h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d5)
	line	116
	
l2928:	
;FrequencyCounterLCD.c: 116: d4=(total/1000) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	03h
	movwf	(?___lldiv+1)
	movlw	0E8h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d4)
	line	117
	
l2930:	
;FrequencyCounterLCD.c: 117: d3=(total/100) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	0
	movwf	(?___lldiv+1)
	movlw	064h
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d3)
	line	118
	
l2932:	
;FrequencyCounterLCD.c: 118: d2=(total/10) %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movlw	0
	movwf	(?___lldiv+3)
	movlw	0
	movwf	(?___lldiv+2)
	movlw	0
	movwf	(?___lldiv+1)
	movlw	0Ah
	movwf	(?___lldiv)

	movf	(main@total+3),w
	movwf	3+(?___lldiv)+04h
	movf	(main@total+2),w
	movwf	2+(?___lldiv)+04h
	movf	(main@total+1),w
	movwf	1+(?___lldiv)+04h
	movf	(main@total),w
	movwf	0+(?___lldiv)+04h

	fcall	___lldiv
	movf	(3+(?___lldiv)),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	3+(?___llmod)+04h
	movf	(2+(?___lldiv)),w
	movwf	2+(?___llmod)+04h
	movf	(1+(?___lldiv)),w
	movwf	1+(?___llmod)+04h
	movf	(0+(?___lldiv)),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d2)
	line	119
	
l2934:	
;FrequencyCounterLCD.c: 119: d1=total %10+48;
	movlw	0
	movwf	(?___llmod+3)
	movlw	0
	movwf	(?___llmod+2)
	movlw	0
	movwf	(?___llmod+1)
	movlw	0Ah
	movwf	(?___llmod)

	movf	(main@total+3),w
	movwf	3+(?___llmod)+04h
	movf	(main@total+2),w
	movwf	2+(?___llmod)+04h
	movf	(main@total+1),w
	movwf	1+(?___llmod)+04h
	movf	(main@total),w
	movwf	0+(?___llmod)+04h

	fcall	___llmod
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	0+(((0+(?___llmod)))),w
	addlw	030h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_d1)
	line	121
	
l2936:	
;FrequencyCounterLCD.c: 121: display(32);
	movlw	(020h)
	fcall	_display
	line	122
	
l2938:	
;FrequencyCounterLCD.c: 122: display(32);
	movlw	(020h)
	fcall	_display
	line	124
;FrequencyCounterLCD.c: 124: if(d7 == 48){display(32); display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d7),w
	xorlw	030h
	skipz
	goto	u2661
	goto	u2660
u2661:
	goto	l2942
u2660:
	
l2940:	
	movlw	(020h)
	fcall	_display
	movlw	(020h)
	fcall	_display
	goto	l2946
	line	125
	
l367:	
	
l2942:	
;FrequencyCounterLCD.c: 125: else{display(d7); display(44); nz=1;}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d7),w
	fcall	_display
	movlw	(02Ch)
	fcall	_display
	
l2944:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@nz)
	bsf	status,0
	rlf	(main@nz),f
	goto	l2946
	
l368:	
	line	126
	
l2946:	
;FrequencyCounterLCD.c: 126: if(d6 == 48 && nz==0){display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d6),w
	xorlw	030h
	skipz
	goto	u2671
	goto	u2670
u2671:
	goto	l2952
u2670:
	
l2948:	
	movf	(main@nz),f
	skipz
	goto	u2681
	goto	u2680
u2681:
	goto	l2952
u2680:
	
l2950:	
	movlw	(020h)
	fcall	_display
	goto	l2956
	line	127
	
l369:	
	
l2952:	
;FrequencyCounterLCD.c: 127: else{display(d6); nz=1;}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d6),w
	fcall	_display
	
l2954:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@nz)
	bsf	status,0
	rlf	(main@nz),f
	goto	l2956
	
l370:	
	line	128
	
l2956:	
;FrequencyCounterLCD.c: 128: if(d5 == 48 && nz==0){display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d5),w
	xorlw	030h
	skipz
	goto	u2691
	goto	u2690
u2691:
	goto	l2962
u2690:
	
l2958:	
	movf	(main@nz),f
	skipz
	goto	u2701
	goto	u2700
u2701:
	goto	l2962
u2700:
	
l2960:	
	movlw	(020h)
	fcall	_display
	goto	l2966
	line	129
	
l371:	
	
l2962:	
;FrequencyCounterLCD.c: 129: else{display(d5); nz=1;}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d5),w
	fcall	_display
	
l2964:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@nz)
	bsf	status,0
	rlf	(main@nz),f
	goto	l2966
	
l372:	
	line	130
	
l2966:	
;FrequencyCounterLCD.c: 130: if(d4 == 48 && nz==0){display(32); display(32);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d4),w
	xorlw	030h
	skipz
	goto	u2711
	goto	u2710
u2711:
	goto	l2972
u2710:
	
l2968:	
	movf	(main@nz),f
	skipz
	goto	u2721
	goto	u2720
u2721:
	goto	l2972
u2720:
	
l2970:	
	movlw	(020h)
	fcall	_display
	movlw	(020h)
	fcall	_display
	goto	l374
	line	131
	
l373:	
	
l2972:	
;FrequencyCounterLCD.c: 131: else{display(d4); display(44);}
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d4),w
	fcall	_display
	movlw	(02Ch)
	fcall	_display
	
l374:	
	line	133
;FrequencyCounterLCD.c: 133: display(d3);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d3),w
	fcall	_display
	line	134
;FrequencyCounterLCD.c: 134: display(d2);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d2),w
	fcall	_display
	line	135
;FrequencyCounterLCD.c: 135: display(d1);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_d1),w
	fcall	_display
	line	136
;FrequencyCounterLCD.c: 136: display(32);
	movlw	(020h)
	fcall	_display
	line	137
;FrequencyCounterLCD.c: 137: display(period);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_period),w
	fcall	_display
	line	138
;FrequencyCounterLCD.c: 138: display(115);
	movlw	(073h)
	fcall	_display
	line	140
	
l2974:	
;FrequencyCounterLCD.c: 140: RB0 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(48/8),(48)&7
	line	141
	
l2976:	
;FrequencyCounterLCD.c: 141: _delay((unsigned long)((1)*(400000/4000.0)));
	opt asmopt_off
movlw	33
movwf	(??_main+0)+0,f
u2747:
decfsz	(??_main+0)+0,f
	goto	u2747
opt asmopt_on

	line	142
	
l2978:	
;FrequencyCounterLCD.c: 142: RB0 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(48/8),(48)&7
	line	143
	
l2980:	
;FrequencyCounterLCD.c: 143: _delay((unsigned long)((1)*(400000/4000.0)));
	opt asmopt_off
movlw	33
movwf	(??_main+0)+0,f
u2757:
decfsz	(??_main+0)+0,f
	goto	u2757
opt asmopt_on

	line	145
	
l2982:	
;FrequencyCounterLCD.c: 145: RB7 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(55/8),(55)&7
	line	146
	
l2984:	
;FrequencyCounterLCD.c: 146: _delay((unsigned long)((1)*(400000/4000.0)));
	opt asmopt_off
movlw	33
movwf	(??_main+0)+0,f
u2767:
decfsz	(??_main+0)+0,f
	goto	u2767
opt asmopt_on

	line	147
	
l2986:	
;FrequencyCounterLCD.c: 147: RB7 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(55/8),(55)&7
	line	148
	
l2988:	
;FrequencyCounterLCD.c: 148: _delay((unsigned long)((1)*(400000/4000.0)));
	opt asmopt_off
movlw	33
movwf	(??_main+0)+0,f
u2777:
decfsz	(??_main+0)+0,f
	goto	u2777
opt asmopt_on

	line	149
;FrequencyCounterLCD.c: 149: }
	goto	l2816
	
l375:	
	line	150
	
l376:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_display
psect	text207,local,class=CODE,delta=2
global __ptext207
__ptext207:

;; *************** function _display *****************
;; Defined at:
;;		line 166 in file "C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
;; Parameters:    Size  Location     Type
;;  fig             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  fig             1    1[COMMON] unsigned char 
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
;;      Locals:         1       0       0       0
;;      Temps:          1       0       0       0
;;      Totals:         2       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_clock
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text207
	file	"C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
	line	166
	global	__size_of_display
	__size_of_display	equ	__end_of_display-_display
	
_display:	
	opt	stack 6
; Regs used in _display: [wreg+status,2+status,0+pclath+cstack]
;display@fig stored from wreg
	movwf	(display@fig)
	line	167
	
l2802:	
;FrequencyCounterLCD.c: 167: RA0=1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(40/8),(40)&7
	line	168
	
l2804:	
;FrequencyCounterLCD.c: 168: PORTB=(fig >> 4); clock();
	movf	(display@fig),w
	movwf	(??_display+0)+0
	movlw	04h
u2545:
	clrc
	rrf	(??_display+0)+0,f
	addlw	-1
	skipz
	goto	u2545
	movf	0+(??_display+0)+0,w
	movwf	(6)	;volatile
	
l2806:	
	fcall	_clock
	line	169
	
l2808:	
;FrequencyCounterLCD.c: 169: PORTB=fig & 0b00001111; clock();
	movf	(display@fig),w
	andlw	0Fh
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	
l2810:	
	fcall	_clock
	line	170
	
l2812:	
;FrequencyCounterLCD.c: 170: RA0=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(40/8),(40)&7
	line	171
	
l385:	
	return
	opt stack 0
GLOBAL	__end_of_display
	__end_of_display:
;; =============== function _display ends ============

	signat	_display,4216
	global	_clear
psect	text208,local,class=CODE,delta=2
global __ptext208
__ptext208:

;; *************** function _clear *****************
;; Defined at:
;;		line 159 in file "C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
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
;;      Temps:          1       0       0       0
;;      Totals:         1       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_clock
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text208
	file	"C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
	line	159
	global	__size_of_clear
	__size_of_clear	equ	__end_of_clear-_clear
	
_clear:	
	opt	stack 6
; Regs used in _clear: [wreg+status,2+status,0+pclath+cstack]
	line	160
	
l2784:	
;FrequencyCounterLCD.c: 160: RA0=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(40/8),(40)&7
	line	161
	
l2786:	
;FrequencyCounterLCD.c: 161: PORTB=0; clock(); PORTB=1; clock();
	clrf	(6)	;volatile
	
l2788:	
	fcall	_clock
	
l2790:	
	movlw	(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	
l2792:	
	fcall	_clock
	line	162
	
l2794:	
;FrequencyCounterLCD.c: 162: PORTB=0; clock(); PORTB=2; clock();
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(6)	;volatile
	
l2796:	
	fcall	_clock
	
l2798:	
	movlw	(02h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	fcall	_clock
	line	163
	
l2800:	
;FrequencyCounterLCD.c: 163: _delay((unsigned long)((2)*(400000/4000.0)));
	opt asmopt_off
movlw	66
movwf	(??_clear+0)+0,f
u2787:
decfsz	(??_clear+0)+0,f
	goto	u2787
	clrwdt
opt asmopt_on

	line	164
	
l382:	
	return
	opt stack 0
GLOBAL	__end_of_clear
	__end_of_clear:
;; =============== function _clear ends ============

	signat	_clear,88
	global	_init
psect	text209,local,class=CODE,delta=2
global __ptext209
__ptext209:

;; *************** function _init *****************
;; Defined at:
;;		line 29 in file "C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
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
;;      Temps:          2       0       0       0
;;      Totals:         2       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_clock
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text209
	file	"C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
	line	29
	global	__size_of_init
	__size_of_init	equ	__end_of_init-_init
	
_init:	
	opt	stack 6
; Regs used in _init: [wreg+status,2+status,0+pclath+cstack]
	line	31
	
l2738:	
;FrequencyCounterLCD.c: 31: CMCON = 0b00000111;
	movlw	(07h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(31)	;volatile
	line	32
;FrequencyCounterLCD.c: 32: T1CON = 0b1110;
	movlw	(0Eh)
	movwf	(16)	;volatile
	line	33
;FrequencyCounterLCD.c: 33: TRISB = 0b11000000;
	movlw	(0C0h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(134)^080h	;volatile
	line	34
;FrequencyCounterLCD.c: 34: TRISA = 0b11110000;
	movlw	(0F0h)
	movwf	(133)^080h	;volatile
	line	35
;FrequencyCounterLCD.c: 35: OPTION = 0b10100000;
	movlw	(0A0h)
	movwf	(129)^080h	;volatile
	line	38
;FrequencyCounterLCD.c: 38: _delay((unsigned long)((100)*(400000/4000.0)));
	opt asmopt_off
movlw	13
movwf	((??_init+0)+0+1),f
	movlw	251
movwf	((??_init+0)+0),f
u2797:
	decfsz	((??_init+0)+0),f
	goto	u2797
	decfsz	((??_init+0)+0+1),f
	goto	u2797
	nop2
opt asmopt_on

	line	39
	
l2740:	
;FrequencyCounterLCD.c: 39: PORTA=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(5)	;volatile
	line	40
	
l2742:	
;FrequencyCounterLCD.c: 40: PORTB=2; clock();
	movlw	(02h)
	movwf	(6)	;volatile
	
l2744:	
	fcall	_clock
	line	41
	
l2746:	
;FrequencyCounterLCD.c: 41: PORTB=2; clock();
	movlw	(02h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	
l2748:	
	fcall	_clock
	line	42
	
l2750:	
;FrequencyCounterLCD.c: 42: PORTB=8; clock();
	movlw	(08h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	
l2752:	
	fcall	_clock
	line	43
	
l2754:	
;FrequencyCounterLCD.c: 43: _delay((unsigned long)((25)*(400000/4000000.0))); _delay((unsigned long)((25)*(400000/4000000.0)));
		opt asmopt_off
	nop2	;2 cycle nop
	opt asmopt_on

	
l2756:	
		opt asmopt_off
	nop2	;2 cycle nop
	opt asmopt_on

	line	44
	
l2758:	
;FrequencyCounterLCD.c: 44: PORTB=0; clock();
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(6)	;volatile
	fcall	_clock
	line	45
	
l2760:	
;FrequencyCounterLCD.c: 45: PORTB=12; clock();
	movlw	(0Ch)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	
l2762:	
	fcall	_clock
	line	46
	
l2764:	
;FrequencyCounterLCD.c: 46: _delay((unsigned long)((25)*(400000/4000000.0))); _delay((unsigned long)((25)*(400000/4000000.0)));
		opt asmopt_off
	nop2	;2 cycle nop
	opt asmopt_on

	
l2766:	
		opt asmopt_off
	nop2	;2 cycle nop
	opt asmopt_on

	line	47
	
l2768:	
;FrequencyCounterLCD.c: 47: PORTB=0; clock(); PORTB=1; clock();
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(6)	;volatile
	
l2770:	
	fcall	_clock
	
l2772:	
	movlw	(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	
l2774:	
	fcall	_clock
	line	48
	
l2776:	
;FrequencyCounterLCD.c: 48: _delay((unsigned long)((2)*(400000/4000.0)));
	opt asmopt_off
movlw	66
movwf	(??_init+0)+0,f
u2807:
decfsz	(??_init+0)+0,f
	goto	u2807
	clrwdt
opt asmopt_on

	line	49
	
l2778:	
;FrequencyCounterLCD.c: 49: PORTB=0; clock();
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(6)	;volatile
	
l2780:	
	fcall	_clock
	line	50
	
l2782:	
;FrequencyCounterLCD.c: 50: PORTB=6; clock();
	movlw	(06h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(6)	;volatile
	fcall	_clock
	line	51
	
l349:	
	return
	opt stack 0
GLOBAL	__end_of_init
	__end_of_init:
;; =============== function _init ends ============

	signat	_init,88
	global	_clock
psect	text210,local,class=CODE,delta=2
global __ptext210
__ptext210:

;; *************** function _clock *****************
;; Defined at:
;;		line 152 in file "C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
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
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_init
;;		_main
;;		_clear
;;		_display
;; This function uses a non-reentrant model
;;
psect	text210
	file	"C:\Users\davidq\Documents\GitHub\electronics\FrequencyMeter - 16F628\Firmware\16f628_FrequencyMeter_2\FrequencyCounterLCD.c"
	line	152
	global	__size_of_clock
	__size_of_clock	equ	__end_of_clock-_clock
	
_clock:	
	opt	stack 7
; Regs used in _clock: []
	line	153
	
l2736:	
;FrequencyCounterLCD.c: 153: RA1=1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(41/8),(41)&7
	line	154
;FrequencyCounterLCD.c: 154: _delay((unsigned long)((25)*(400000/4000000.0)));
		opt asmopt_off
	nop2	;2 cycle nop
	opt asmopt_on

	line	155
;FrequencyCounterLCD.c: 155: RA1=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	line	156
;FrequencyCounterLCD.c: 156: _delay((unsigned long)((25)*(400000/4000000.0)));
		opt asmopt_off
	nop2	;2 cycle nop
	opt asmopt_on

	line	157
	
l379:	
	return
	opt stack 0
GLOBAL	__end_of_clock
	__end_of_clock:
;; =============== function _clock ends ============

	signat	_clock,88
	global	___lldiv
psect	text211,local,class=CODE,delta=2
global __ptext211
__ptext211:

;; *************** function ___lldiv *****************
;; Defined at:
;;		line 5 in file "C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\lldiv.c"
;; Parameters:    Size  Location     Type
;;  divisor         4    0[COMMON] unsigned long 
;;  dividend        4    4[COMMON] unsigned long 
;; Auto vars:     Size  Location     Type
;;  quotient        4    9[COMMON] unsigned long 
;;  counter         1   13[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[COMMON] unsigned long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         8       0       0       0
;;      Locals:         5       0       0       0
;;      Temps:          1       0       0       0
;;      Totals:        14       0       0       0
;;Total ram usage:       14 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text211
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\lldiv.c"
	line	5
	global	__size_of___lldiv
	__size_of___lldiv	equ	__end_of___lldiv-___lldiv
	
___lldiv:	
	opt	stack 7
; Regs used in ___lldiv: [wreg+status,2+status,0]
	line	9
	
l2712:	
	movlw	0
	movwf	(___lldiv@quotient+3)
	movlw	0
	movwf	(___lldiv@quotient+2)
	movlw	0
	movwf	(___lldiv@quotient+1)
	movlw	0
	movwf	(___lldiv@quotient)

	line	10
	movf	(___lldiv@divisor+3),w
	iorwf	(___lldiv@divisor+2),w
	iorwf	(___lldiv@divisor+1),w
	iorwf	(___lldiv@divisor),w
	skipnz
	goto	u2471
	goto	u2470
u2471:
	goto	l2732
u2470:
	line	11
	
l2714:	
	clrf	(___lldiv@counter)
	bsf	status,0
	rlf	(___lldiv@counter),f
	line	12
	goto	l2718
	
l966:	
	line	13
	
l2716:	
	movlw	01h
	movwf	(??___lldiv+0)+0
u2485:
	clrc
	rlf	(___lldiv@divisor),f
	rlf	(___lldiv@divisor+1),f
	rlf	(___lldiv@divisor+2),f
	rlf	(___lldiv@divisor+3),f
	decfsz	(??___lldiv+0)+0
	goto	u2485
	line	14
	movlw	(01h)
	movwf	(??___lldiv+0)+0
	movf	(??___lldiv+0)+0,w
	addwf	(___lldiv@counter),f
	goto	l2718
	line	15
	
l965:	
	line	12
	
l2718:	
	btfss	(___lldiv@divisor+3),(31)&7
	goto	u2491
	goto	u2490
u2491:
	goto	l2716
u2490:
	goto	l2720
	
l967:	
	goto	l2720
	line	16
	
l968:	
	line	17
	
l2720:	
	movlw	01h
	movwf	(??___lldiv+0)+0
u2505:
	clrc
	rlf	(___lldiv@quotient),f
	rlf	(___lldiv@quotient+1),f
	rlf	(___lldiv@quotient+2),f
	rlf	(___lldiv@quotient+3),f
	decfsz	(??___lldiv+0)+0
	goto	u2505
	line	18
	
l2722:	
	movf	(___lldiv@divisor+3),w
	subwf	(___lldiv@dividend+3),w
	skipz
	goto	u2515
	movf	(___lldiv@divisor+2),w
	subwf	(___lldiv@dividend+2),w
	skipz
	goto	u2515
	movf	(___lldiv@divisor+1),w
	subwf	(___lldiv@dividend+1),w
	skipz
	goto	u2515
	movf	(___lldiv@divisor),w
	subwf	(___lldiv@dividend),w
u2515:
	skipc
	goto	u2511
	goto	u2510
u2511:
	goto	l2728
u2510:
	line	19
	
l2724:	
	movf	(___lldiv@divisor),w
	subwf	(___lldiv@dividend),f
	movf	(___lldiv@divisor+1),w
	skipc
	incfsz	(___lldiv@divisor+1),w
	subwf	(___lldiv@dividend+1),f
	movf	(___lldiv@divisor+2),w
	skipc
	incfsz	(___lldiv@divisor+2),w
	subwf	(___lldiv@dividend+2),f
	movf	(___lldiv@divisor+3),w
	skipc
	incfsz	(___lldiv@divisor+3),w
	subwf	(___lldiv@dividend+3),f
	line	20
	
l2726:	
	bsf	(___lldiv@quotient)+(0/8),(0)&7
	goto	l2728
	line	21
	
l969:	
	line	22
	
l2728:	
	movlw	01h
u2525:
	clrc
	rrf	(___lldiv@divisor+3),f
	rrf	(___lldiv@divisor+2),f
	rrf	(___lldiv@divisor+1),f
	rrf	(___lldiv@divisor),f
	addlw	-1
	skipz
	goto	u2525

	line	23
	
l2730:	
	movlw	low(01h)
	subwf	(___lldiv@counter),f
	btfss	status,2
	goto	u2531
	goto	u2530
u2531:
	goto	l2720
u2530:
	goto	l2732
	
l970:	
	goto	l2732
	line	24
	
l964:	
	line	25
	
l2732:	
	movf	(___lldiv@quotient+3),w
	movwf	(?___lldiv+3)
	movf	(___lldiv@quotient+2),w
	movwf	(?___lldiv+2)
	movf	(___lldiv@quotient+1),w
	movwf	(?___lldiv+1)
	movf	(___lldiv@quotient),w
	movwf	(?___lldiv)

	goto	l971
	
l2734:	
	line	26
	
l971:	
	return
	opt stack 0
GLOBAL	__end_of___lldiv
	__end_of___lldiv:
;; =============== function ___lldiv ends ============

	signat	___lldiv,8316
	global	___llmod
psect	text212,local,class=CODE,delta=2
global __ptext212
__ptext212:

;; *************** function ___llmod *****************
;; Defined at:
;;		line 5 in file "C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\llmod.c"
;; Parameters:    Size  Location     Type
;;  divisor         4    0[BANK0 ] unsigned long 
;;  dividend        4    4[BANK0 ] unsigned long 
;; Auto vars:     Size  Location     Type
;;  counter         1    9[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] unsigned long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       8       0       0
;;      Locals:         0       1       0       0
;;      Temps:          0       1       0       0
;;      Totals:         0      10       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text212
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\llmod.c"
	line	5
	global	__size_of___llmod
	__size_of___llmod	equ	__end_of___llmod-___llmod
	
___llmod:	
	opt	stack 7
; Regs used in ___llmod: [wreg+status,2+status,0]
	line	8
	
l2692:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(___llmod@divisor+3),w
	iorwf	(___llmod@divisor+2),w
	iorwf	(___llmod@divisor+1),w
	iorwf	(___llmod@divisor),w
	skipnz
	goto	u2411
	goto	u2410
u2411:
	goto	l2708
u2410:
	line	9
	
l2694:	
	clrf	(___llmod@counter)
	bsf	status,0
	rlf	(___llmod@counter),f
	line	10
	goto	l2698
	
l947:	
	line	11
	
l2696:	
	movlw	01h
	movwf	(??___llmod+0)+0
u2425:
	clrc
	rlf	(___llmod@divisor),f
	rlf	(___llmod@divisor+1),f
	rlf	(___llmod@divisor+2),f
	rlf	(___llmod@divisor+3),f
	decfsz	(??___llmod+0)+0
	goto	u2425
	line	12
	movlw	(01h)
	movwf	(??___llmod+0)+0
	movf	(??___llmod+0)+0,w
	addwf	(___llmod@counter),f
	goto	l2698
	line	13
	
l946:	
	line	10
	
l2698:	
	btfss	(___llmod@divisor+3),(31)&7
	goto	u2431
	goto	u2430
u2431:
	goto	l2696
u2430:
	goto	l2700
	
l948:	
	goto	l2700
	line	14
	
l949:	
	line	15
	
l2700:	
	movf	(___llmod@divisor+3),w
	subwf	(___llmod@dividend+3),w
	skipz
	goto	u2445
	movf	(___llmod@divisor+2),w
	subwf	(___llmod@dividend+2),w
	skipz
	goto	u2445
	movf	(___llmod@divisor+1),w
	subwf	(___llmod@dividend+1),w
	skipz
	goto	u2445
	movf	(___llmod@divisor),w
	subwf	(___llmod@dividend),w
u2445:
	skipc
	goto	u2441
	goto	u2440
u2441:
	goto	l2704
u2440:
	line	16
	
l2702:	
	movf	(___llmod@divisor),w
	subwf	(___llmod@dividend),f
	movf	(___llmod@divisor+1),w
	skipc
	incfsz	(___llmod@divisor+1),w
	subwf	(___llmod@dividend+1),f
	movf	(___llmod@divisor+2),w
	skipc
	incfsz	(___llmod@divisor+2),w
	subwf	(___llmod@dividend+2),f
	movf	(___llmod@divisor+3),w
	skipc
	incfsz	(___llmod@divisor+3),w
	subwf	(___llmod@dividend+3),f
	goto	l2704
	
l950:	
	line	17
	
l2704:	
	movlw	01h
u2455:
	clrc
	rrf	(___llmod@divisor+3),f
	rrf	(___llmod@divisor+2),f
	rrf	(___llmod@divisor+1),f
	rrf	(___llmod@divisor),f
	addlw	-1
	skipz
	goto	u2455

	line	18
	
l2706:	
	movlw	low(01h)
	subwf	(___llmod@counter),f
	btfss	status,2
	goto	u2461
	goto	u2460
u2461:
	goto	l2700
u2460:
	goto	l2708
	
l951:	
	goto	l2708
	line	19
	
l945:	
	line	20
	
l2708:	
	movf	(___llmod@dividend+3),w
	movwf	(?___llmod+3)
	movf	(___llmod@dividend+2),w
	movwf	(?___llmod+2)
	movf	(___llmod@dividend+1),w
	movwf	(?___llmod+1)
	movf	(___llmod@dividend),w
	movwf	(?___llmod)

	goto	l952
	
l2710:	
	line	21
	
l952:	
	return
	opt stack 0
GLOBAL	__end_of___llmod
	__end_of___llmod:
;; =============== function ___llmod ends ============

	signat	___llmod,8316
psect	text213,local,class=CODE,delta=2
global __ptext213
__ptext213:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
