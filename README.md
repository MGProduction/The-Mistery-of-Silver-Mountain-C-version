# The-Mistery-of-Silver-Mountain-C-version
This is a C "translation" of *The Mystery of Silver Mountain* (1984), originally written in BASIC by **Chris Oxlade** and **Judy Tatchell** for **Usborne Publishing**.

```
          MYSTERY OF SILVER
              MOUNTAIN
========================================


GOOD LUCK ON YOUR QUEST!. YOU ARE AT A
CROSSROADS AND YOU CAN GO E,W,

========================================


WHAT WILL YOU DO NOW 
?
```

This version goes beyond a straightforward BASIC-to-C rewrite: it aims to enhance readability by "decrypting" the original code, which was intentionally obfuscated—both to save space and to avoid revealing spoilers to users typing it into their 8-bit machines. The goal is to make the code easier to understand and more accessible for future translations into other languages or platforms.

That said, this version remains as faithful as possible to the original game logic and structure. No changes have been made to the adventure content itself, except for avoiding the use of GOTO statements in favor of more structured code.

A PDF copy of the book is still available from Usborne's website here: https://usborne.com/gb/books/computer-and-coding-books.

All credit must go to the authors: Chris Oxlade and Judy Tatchell, and copyright holders Usborne Publishing.

## Why?

I'm working on a translation (adding graphics and some extra features) of this great adventure game in StoryTllr, and I needed a way to ensure that I don't miss some of the original features. Working MORE on the original code was then *mandatory*.

## What?

The main difference between readable and unreadable code lies in the use of named constants instead of raw numbers, and in choosing clear, self-explanatory names for variables and functions. So, my work here was fairly straightforward. In this particular case, the original code also used a simple encryption algorithm to obscure some of the in-game strings. I’ve decoded those strings so that everything is now fully understandable.

## Extras

To be sure the game was fully playable I've added a modality to "run" a file with a sequence of passages (i.e. c_silvermountain bin/game_walkthrough.txt) - as did Ben Holland (see later on). This helped me to do some changes in my code (bugfixes) AND to write the game_walkthrough.txt file (created using **Dorothy Millard**'s work) with some minor but needed changes. Playing the walkthrough using the automatic way takes you to the LAST action of the game (when you have to say the last magic word) - so everything should work.

If you want to reach a specific part of the game you can put a line with just 
```
#
```
where you want in the walkthrough file, start the game invoking it, wait a few seconds and you'll be able to play from that point forward. You can also write your own walkthrough file - even adding (after the command) a comment starting with # (i.e. 
```
examine pot # it's important!
```
)

## References
I've decided to work on a C translation of the original source code after having seen the great work done by **Ben Holland** (https://github.com/fivegreenapples/go-mountain/tree/main) who did a **Golang** translation. I've worked with his code for a while (deobfuscating it) and I thought it was interesting doing the work of **C** code instead.
