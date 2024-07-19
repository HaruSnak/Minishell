<img src="readme/pipex.png" alt="pipex" width="900"/>

# Pipex
**Pipex** is a project from the 42 curriculum that immerses you in the realm of **Linux pipes**. It involves replicating the functionality of pipes in Linux, providing a deeper understanding of their inner workings.<br>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

## 📒 Index

- [About](#about)
- [Approach](#approach)
  - [Installation](#installation)
- [Development](#development)
  <!--- [Pre-Requisites](#pre-requisites)-->
  - [File Structure](#file-structure)
  <!-- [Diagram Architecture](#diagram-architecture)  -->
- [Notes](#notes)
- [Credits](#credits)

## About

Picture a water pipeline: each command acts as a filter, processing data and sending the output to the next command in the pipeline. Pipex allows you to create a similar pipeline for computer data.<br>

* **User-Provided Commands**: *These commands can be basic Linux utilities like cat (displaying file contents), grep (filtering text), wc (counting lines/words/characters), or even your own custom C programs.*<br>
* **Connecting Commands with Pipes**: *Using pipes, Pipex establishes a communication channel between commands. The standard output of the first command becomes the standard input of the next. This way, data processed by one command is directly fed into the next for further processing.*<br>
* **Final Result**: *The data, transformed by the various commands in the pipeline, emerges from the last command and is displayed on the screen.*<br>

## Approach

This project turned out to be a captivating experience for me, as it went beyond mere C programming and presented a significant algorithmic challenge. If you're a beginner in this field seeking a stimulating challenge, look no further.<br>

I had already heard about the various algorithmic approaches employed by other students for this project, including the renowned "Mechanical Turk" method. However, the idea of resorting to a ready-made solution didn't sit well with me. So, I decided to put my thinking cap on and devise an efficient way to sort unique random numbers, whether positive or negative.<br>

The idea came to me to pre-sort the numbers in a list to identify the appropriate element to move. However, a second challenge presented itself: I was familiar with the concept of linked lists, but using them didn't bring me any joy.<br>

Therefore, I decided to seize this opportunity to solve two problems at once by implementing the project using linked lists. I devoted considerable time to this project, particularly focusing on optimizing "push" instructions.<br>

In the end, I realized that I had invested far more time than anticipated, and the bitter taste of the instructions didn't align with my initial goal.<br>

Despite these mixed feelings, this project has enabled me to acquire a wealth of valuable knowledge and skills.<br>

### **Push Swap Results:**

**100 Numbers:**

* **Worst = 795 instructions**
* **Median = 727 instructions**
* **Best = 652 instructions**

**500 Numbers:**

* **Worst = 7963 instructions**
* **Median = 7522 instructions**
* **Best = 7044 instructions**

## Installation
```bash
# Clone this repository
$ git clone https://github.com/HaruSnak/So_Long.git

# Go into the repository
$ cd So_Long

# To compile the program
$ make

# Execution example
$ ./so_long {NAME_MAP}.ber

# Allows you to do a complete cleaning of your construction environment
$ make fclean # Or make clean
```

## Development
### Pre-Requisites
```
Requirements for Linux

MinilibX only support TrueColor visual type (8,15,16,24 or 32 bits depth)
gcc
make
X11 include files (package xorg)
XShm extension must be present (package libxext-dev)
Utility functions from BSD systems - development files (package libbsd-dev)
e.g. sudo apt-get install gcc make xorg libxext-dev libbsd-dev (Debian/Ubuntu)
```

### File Structure

```
.
└── 📁pipex
    └── Makefile
    └── 📁includes
        └── 📁libft
            └── Makefile
            └── 📁char
                └── ft_isalnum.c
                └── ft_isalpha.c
                └── ft_isascii.c
                └── ft_isdigit.c
                └── ft_isprint.c
                └── ft_tolower.c
                └── ft_toupper.c
            └── 📁conv
                └── ft_atoi.c
                └── ft_itoa.c
            └── 📁gnl
                └── get_next_line.c
            └── 📁includes
                └── libft.h
            └── 📁lst
                └── ft_lstadd_back_bonus.c
                └── ft_lstadd_front_bonus.c
                └── ft_lstclear_bonus.c
                └── ft_lstdelone_bonus.c
                └── ft_lstiter_bonus.c
                └── ft_lstlast_bonus.c
                └── ft_lstmap_bonus.c
                └── ft_lstnew_bonus.c
                └── ft_lstsize_bonus.c
            └── 📁mem
                └── ft_bzero.c
                └── ft_calloc.c
                └── ft_memchr.c
                └── ft_memcmp.c
                └── ft_memcpy.c
                └── ft_memmove.c
                └── ft_memset.c
            └── 📁printf
                └── ft_conv_primary.c
                └── ft_conv_specifies.c
                └── ft_conv_suit.c
                └── ft_printf.c
            └── 📁put
                └── ft_putchar.c
                └── ft_putchar_fd.c
                └── ft_putendl_fd.c
                └── ft_putnbr.c
                └── ft_putnbr_fd.c
                └── ft_putstr.c
                └── ft_putstr_fd.c
            └── 📁str
                └── ft_split.c
                └── ft_strchr.c
                └── ft_strdup.c
                └── ft_striteri.c
                └── ft_strjoin.c
                └── ft_strlcat.c
                └── ft_strlcpy.c
                └── ft_strlen.c
                └── ft_strmapi.c
                └── ft_strncmp.c
                └── ft_strnstr.c
                └── ft_strrchr.c
                └── ft_strtrim.c
                └── ft_substr.c
        └── pipex.h
    └── input
    └── 📁srcs
        └── 📁bonus
        └── errors.c
        └── find_path.c
        └── 📁input
        └── pipex.c
```

### Diagram Architecture
Write the build Instruction here.

## Notes

*Small error on my part, for which there is a good chance that I will re-push the correction to get 100/100*
<p align="left">
    <img src="https://image.noelshack.com/fichiers/2024/29/4/1721314123-sans-titre.png"
         alt="Sponsored by Evil Martians" width="216" height="164">
</p>

## Credits

Below you will find the links used for this project:

- [Norm 42](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- [Mechanical Turk](https://en.wikipedia.org/wiki/Amazon_Mechanical_Turk)
- [Fred Orion | Similar method | inspiration](https://www.youtube.com/watch?v=2aMrmWOgLvU)

[contributors-shield]: https://img.shields.io/github/contributors/HaruSnak/So_long.svg?style=for-the-badge
[contributors-url]: https://github.com/HaruSnak/So_Long/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/HaruSnak/So_Long.svg?style=for-the-badge
[forks-url]: https://github.com/HaruSnak/So_Long/network/members
[stars-shield]: https://img.shields.io/github/stars/HaruSnak/So_Long.svg?style=for-the-badge
[stars-url]: https://github.com/HaruSnak/So_Long/stargazers
[issues-shield]: https://img.shields.io/github/issues/HaruSnak/So_Long.svg?style=for-the-badge
[issues-url]: https://github.com/HaruSnak/So_Long/issues
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/shany-moreno-5a863b2aa
