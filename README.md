# Scream
> AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
> \- A wise screamlang programmer.

Alright, so the premise is Brainfuck, but existential crisis. The implementation
would go like this:

* Write brainfuck interpreter
* Transalate brainuck commands (like ">") into existential 
  crisis commands (like "A"), so: `>>>>>` becomes `AAAAA`.
* Steal brainfuck examples from the internet and use a custom
  vim script to automatically transalate, it would probably be
  placed in [scripts/macro.vim](/scripts/macro.vim), and would
  consist of find and replace procedures.
* Profit!

So yeah, that's what I'm going to do.

## Install
```sh
git clone https://github.com/ElisStaaf/scream
cd scream

make              # To build
sudo make install # To install
```

## Examples
This is a simple hello world program:
```console
UUUUUUUUuAUUUUuAUUAUUUAUUUAUEEEEOoAUAU
AOAAUuEoEOoAAeAOOOeUUUUUUUeeUUUeAAeEOe
EeUUUeOOOOOOeOOOOOOOOeAAUeAUUe
```
See more in [examples](/examples).
