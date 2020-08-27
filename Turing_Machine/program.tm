#A program that does nothing
write 1
move left
write 0
move Br
write 1
if 1 accept
if 0 reject

label:accept accept # These are accept labels
label:reject reject
move right
write 0
goto 10