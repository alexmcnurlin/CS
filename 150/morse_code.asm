
; Just some configuration for the text editor
; vim fdm=manual
.org 0x100


ENTRY:
  LDI r16, 0xFF
  LDI r17, 0x00
  LDI r18, -1       
  OUT 0x04, r16     ; This enables writing to output 0x05

  RCALL NAME
  RCALL WAIT
  RCALL WAIT
  RCALL WAIT
  RCALL WAIT
  RCALL WAIT
  RCALL WAIT
  RCALL WAIT
  JMP ENTRY         ; Rinse and repeat

LED_ON:             ; Turns the LED on
  OUT 0x05, r16     ; Write to output
  ;CALL WAIT         ; Wait one second
  ;JMP LED_OFF       ; Turn the LED off
  RET
  

LED_OFF:            ; Turns the LED off
  OUT 0x05, r17     ; Write to output
  ;CALL WAIT         ; Wait one second
  ;JMP LED_ON        ; Turn the LED on
  RET

WAIT:               ; Launches a series of nested loops to wait 1 second
  LDI r19, 255      ; Starting values to be decremented
  LDI r20, 255      ; These values were chose fairly arbitrarily, choosing
  LDI r21, 10       ;   whatever made a time of one second
BR:
  ADD r19, r18      ; Decrement r17 by 1
  BRBC 1, BR        ; If r19 is not 0, keep looping
  ADD r20, r18      ; Decrement r17 by 1
  NOP               ; Wait one instruction, just to waste time
  BRBC 1, BR        ; If r17 is not 0, keep looping
  ADD r21, r18      ; Decrement r17 by 1
  NOP               ; Wait one instruction, just to waste time
  BRBC 1, BR        ; If r17 is not 0, keep looping
  RET               ; Returns when r17 is 0


DOT:
  RCALL LED_ON
  RCALL WAIT
  RCALL LED_OFF
  RCALL WAIT
  RET

DASH:
  RCALL LED_ON
  RCALL WAIT
  RCALL WAIT
  RCALL WAIT
  RCALL LED_OFF
  RCALL WAIT
  RET

SPACE:
  RCALL WAIT
  RCALL WAIT
  RCALL WAIT
  RET

;Alphabet:
;  CALL A
;  CALL B
;  CALL C
;  CALL D
;  CALL E
;  CALL F
;  CALL G
;  CALL H
;  CALL I
;  CALL J
;  CALL K
;  CALL L
;  CALL M
;  CALL N
;  CALL O
;  CALL P
;  CALL Q
;  CALL R
;  CALL S
;  CALL T
;  CALL U
;  CALL V
;  CALL W
;  CALL X
;  CALL Y
;  CALL Z

NAME:
  RCALL A
  RCALL L
  RCALL E
  RCALL X
  RET

A:
  RCALL DOT
  RCALL DASH
  RCALL SPACE
  RET

L: 
  RCALL DOT
  RCALL DASH
  RCALL DOT
  RCALL DOT
  RCALL SPACE
  RET

E:
  RCALL DOT
  RCALL SPACE
  RET

X:
  RCALL DASH
  RCALL DOT
  RCALL DOT
  RCALL DASH
  RCALL SPACE
  RET
