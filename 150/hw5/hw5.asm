; Just some configuration for the text editor
; vim fdm=manual
.org 0x00


ENTRY:
  LDI r16, 0xFF
  LDI r17, 0x00
  LDI r18, -1       
  OUT 0x04, r16     ; This enables writing to output 0x05


LED_ON:             ; Turns the LED on
  OUT 0x05, r16     ; Write to output
  CALL WAIT         ; Wait one second
  JMP LED_OFF       ; Turn the LED off
  

LED_OFF:            ; Turns the LED off
  OUT 0x05, r17     ; Write to output
  CALL WAIT         ; Wait one second
  JMP LED_ON        ; Turn the LED on

WAIT:               ; Launches a series of nested loops to wait 1 second
  LDI r19, 255      ; Starting values to be decremented
  LDI r20, 255      ; These values were chose fairly arbitrarily, choosing
  LDI r21, 81       ;   whatever made a time of one second
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

  JMP ENTRY         ; Rinse and repeat
