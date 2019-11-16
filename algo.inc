
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

                stz z_d                     
                lda CursorY     
                clc
                adc z_e                         ;Add carry to M byte
                tay
                lda z_d
                adc #0                          ;Add carry to H byte
                sta z_d
                stz z_e
                lda CursorX     
                asl
                rol z_e
                tax                        
                tya                       
                adc z_e
                tay                      
                lda z_d                 
                adc #$10               

                jsr SetVeraADDR        
		rts

.string !pet	"testing x y coords - waiting for enter...",13,0
!src "grid.inc"
