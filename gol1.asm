zr = $20          ;get zome zero page vars to work with

z_hl = zr         ;hl Pair
z_l  = zr
z_h  = zr+1

z_de = zr+4       ;de pair
z_e  = zr+4
z_d  = zr+5

z_as = zr+6       ;hold a

CursorX = zr+7
CursorY = zr+8
Character = zr+9
Colour = zr+10

ach = zr+12

aa = zr+14 		;to store regs that would be sent to vera to build action list
ax = zr+15
ay = zr+16
nn = zr+17		;neighbor count

bx = zr+20		; hold current cursor for checking square
by = zr+21

mkll = zr+22		; build a list at this address, initially set to list base
mklh = zr+23		; high byte
mkly = zr+24		; store current list Y indirect index register
sx = zr+25		; store X in list
sy = zr+26		; store Y in list
sc = zr+27		; store char in list

!src "vera.inc"
*=$0801			; Assembled code should start at $0801
			; (where BASIC programs start)
			; The real program starts at $0810 = 2064
!byte $0C,$08		; $080C - pointer to next line of BASIC code
!byte $0A,$00		; 2-byte line number ($000A = 10)
!byte $9E		; SYS BASIC token
!byte $20		; [space]
!byte $32,$30,$36,$34	; $32="2",$30="0",$36="6",$34="4"
			; (ASCII encoded nums for dec starting addr)
!byte $00		; End of Line
!byte $00,$00		; This is address $080C containing
			; 2-byte pointer to next line of BASIC code
			; ($0000 = end of program)
*=$0810			; Here starts the real program
+video_init
+vset $00000 | AUTO_INC_1 ; VRAM bank 0

CHROUT=$FFD2		; CHROUT outputs a character (C64 Kernal API)
CHRIN=$FFCF		; CHRIN read from default input
CURRENT=$0

start:
	lda #32 	; space
	sta Character
	lda #3		; light blue
	sta Colour
	jsr fullscreen

	lda #$2A	; star
	sta Character

	lda #2 		; red
	lda #7 		; yellow
	sta Colour

	jsr veraprint

	jsr readlist

	jsr CHRIN
	jsr CHRIN

	lda #32
	sta Character
	jsr fullscreen

	jsr initlist

	lda #$2a
	sta sc
	lda #40
	sta sx
	sta sy
	jsr storeaction
	lda #41
	sta sx
	sta sy
	jsr storeaction
	lda #42
	sta sx
	sta sy
	jsr storeaction
	lda #255		; terminate the list
	sta sx
	sta sy
	sta sc
	jsr storeaction

	jsr readlist

	rts



!src "readlist.inc"

!src "makelist.inc"		; removing this src, even though its labels are never called
				; will make it work gagin
	

fullscreen:
	lda #79
	sta CursorX
	lda #59
	sta CursorY
goleft:
	jsr column
	dec CursorX
	bne goleft
	jsr column
	rts		; Return to caller

column:
	jsr veraprint
	dec CursorY
	bne column
	jsr veraprint
	lda #59
	sta CursorY
	rts
	

veraprint:
	pha
	phy
	phx
	; set the memory addr
	jsr sexy
	; send the char to VERA at x y
	ldy Character
	sty veradat
	ldy Colour
	sty veradat
	plx
	ply
	pla
	rts

SetVeraADDR:             
                        
		; A contains vera Hi addr,
		; Y contains vera mid
		; X contains vera lo

		; -- comment - could I use X and Y regs directly
		; -- instead of my Zero page surrogates? Hmm

                sta verahi
                sty veramid
                stx veralo
		rts

sexy:
		lda CursorX
		asl  ; mul 2
		tax ; put lo byte into x
		lda #0
		rol  ; get 9th bit
		adc CursorY ; add Y*256 effectivly
		tay ; put mi byte into y
		lda #$10 ; set incremement
		jsr SetVeraADDR
		rts

.string !pet	"testing x y coords - waiting for enter...",13,0
!src "grid.inc"

