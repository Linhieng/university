stack segment stack use16 'stack'
    dw 32 dup(0)
stack    ends

data segment
io8255a        equ 28ah
io8255b        equ 28bh
portc1  db  24h,44h,04h,44h,04h,44h,04h   ; 控制 L6 的闪烁 44h,04h
        db  81h,82h,80h,82h,80h,82h,80h   ; 控制 L1 的闪烁 82h,80h
        db  0ffh                          ; 结束标志

data ends
code  segment
      assume  cs:code,ds:data
start:
    ; 这里是对输出端口的相关初始化
    mov   ax,data
    mov   ds,ax
    mov   dx,io8255b
    mov   al,90h
    out   dx,al           ;设置8255为C口输出
    mov   dx,io8255a


re_on:    mov   bx,0
on:    mov   al,portc1[bx] ; 将 PORTC1 中的值送到 AL
    cmp   al,0ffh ; 当 al 的值为 offh 时，就重新开始闪烁，因为 portcl 中都输出过了
    jz    re_on

    ; 这里是调试作用，看看当前的 al 是哪一个值（即当前的 portc1 的偏移量）
    push dx
    push ax
    mov dl, al
    mov ah, 2
    int 21h
    pop ax
    pop dx

    ;
    ; cx 控制的是下面 loop de1 的循环次数。外循环
    ; di 这里控制的是 jnz de0 的循环次数。内循环
    ;

    out   dx, al    ; 点亮相应的灯
    inc   bx        ; bx++ 改变闪烁

    ; 这里的 cx 控制的是闪烁的时间
    mov   cx,200          ; 闪 200ms，暗 200ms
    test  al,21h          ; 判断是否有绿灯亮
    jz    de1             ; 判断没亮，说明此时是在闪烁，则直接使用上面的 cx （控制闪烁时间）

    ; 这里的 cx 控制的是 红绿灯亮的时间
    mov   cx, 30000         ; 30s(30,000ms)绿灯亮，则修改 cx ，让后面的循环执行久一点，实现长延时

 de1: mov   di ,45     ; 设置内循环的次数. 此处设置 di 为 45，能够实现内循环循环45次时，执行的时间为 1ms

    ; 外循环，通过输出相关内容，实现调试加延长循环执行时间
    push dx
    push ax
    mov dl, 2dh
    mov ah, 2
    int 21h
    pop ax
    pop dx

 de0:  dec di

    ; 内循环，通过输出相关内容，实现调试加延长循环执行时间
    push dx
    push ax
    mov dl, 2eh
    mov ah, 2
    int 21h
    pop ax
    pop dx

    ; 继续内循环，执行 di 次
    jnz de0
    ; 继续外循环，执行 cx 次
    loop  de1









    ; 检测是否有输入, 如果有输入则退出
    push dx
    mov ah,06h
    mov dl,0ffh
    int 21h
    pop dx


    ; 这里实现的就是 红绿黄灯的切换
    jz  on                ; 键盘没有输入，回到 on，继续循环


exit:    mov   ah,4ch          ; 返回
    int   21h
code ends
    end start



; 最后再对代码进行相关补充说明：
; portc1 变量的内容，指的就是8个led灯的亮灭，亮灭分别是0和1，所以8个灯的亮灭可以使用两位16进制来表示。比如24h就是00100100，即第三个灯和第六个灯亮，其余灯灭（从右边开始数）这亮的两个灯就是红灯和绿灯。依次类推，44h就是黄灯亮，绿灯灭，04h就是只有红灯，故24h 44h 04h 44h 04h 44h 04h 代表的就是，先红绿灯亮，然后绿灯灭且黄灯亮，然后黄灯灭，黄灯亮，即黄灯闪烁三次。后面的81h,82h,80h,82h,80h,82h,80h也是同样的道理，只不过方向反了过来而已。而0ffh代表的就是结束，没有任何一个灯会亮。
; 后面的 re_on 控制的是 portc1 变量的循环，当灯的变化执行到0ffh时，就需要重新开始执行一遍了，这里面的bx就是代表portc1中的偏移量，即表示当前灯的亮灭情况是哪种，是24h，还是44h，还是04h或是其他。
; 后面的一段push和pop是用于查看当前是取出了哪个portc1值，方便调试。
; 然后再后面遇到的第一个重点就是jz   de1，这条命令在 test 命令后执行，作用就是检测当前是否有绿灯亮，因为前面已经说过了，我们是通过循环来控制延时的，而绿灯亮的时长和黄灯闪烁的时长是不一样的，所以此处需要判断一下当前是不是绿灯亮，如果是绿灯亮，那么我们需要将延时的时间设置的更长一点；如果此时绿灯没亮，说明此时是在闪烁，所以延时的时间会短一点。此时的实现就是先将延时的时间设置为闪烁的时间，然后如果判断得出此时绿灯亮，就将延时时间修改的更长一点，即30秒。
; 再后面的 de0 和 de1 就是内外循环了。内循环的实现	主要的代码就是 jnz de0 代表，他是实现内循环的关键，所以de0程序段也是内循环程序段，di就是内循环次数。外循环的实现主要代码就是loop  de1，所以de1程序段是外循环程序段，cx控制的是外循环次数。
; 最后面的部分，就是检测一下用户是否在键盘上有输入，如果有输入，则退出循环，没有输入，则通过jz  on继续重新开始。

; 最后简单梳理一下程序的过程：
; 首先进行相关初始化
; 然后取出portc1中的一个变量
; 通过取出的变量，让led灯执行对应的亮灭
; 然后执行内外循环，此时的作用就是让led灯保持一定时间的状态（亮灭）
; 内外循环执行结束后，判断一下是否有输入
; 如果没有输入，则重复上面的操作，取出下一个变量继续循环。
