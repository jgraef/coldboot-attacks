# Seminar topic: Cold Boot Attacks

This repository contains materials about our seminar topic *Cold Boot Attacks*.

Information about this seminar can be found here: <https://trust.cispa.saarland/teaching/SS17/hacking.html>

## Presentation

Our presentation slides are provided as `coldboot.pdf`.

## Programs

We implemented small programs to fill memory before the cold boot and read it afterwards:

* `fill_mem.c`: Used during testing to fill memory with a magic string (`**ColdBoot**`). After reboot we were able to grep for this string (`dd if=/dev/mem | strings | grep ColdBoot`).
* `find_string.c`: A small program that searches memory for the string `ColdBoot`.
* `find_key.c`: Searches memory for private SSH keys.

