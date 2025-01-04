# Scream
> AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA  
> \- A wise screamlang programmer.

Alright, so the premise is Brainfuck, but existential crisis. The implementation
would go like this:

* Write brainfuck interpreter
* Transalate brainfuck commands (like ">") into existential 
  crisis commands (like "A"), so: `>>>>>` becomes `AAAAA`.
* Steal brainfuck examples from the internet and use a custom
  vim script to automatically transalate, it would probably be
  placed in [scripts/macro.vim](/scream/scripts/macro.vim), and would
  consist of find and replace procedures.
* Profit!

So yeah, that's what I'm going to do. Screamlang is a programming language for wheen you
need to take out your frustration. For example, `AAeueAAeueueAAAOOoooeuueuAEEEueueeeEeu`
is a valid instruction in scream. And I don't know about you, but that's *exactly* how
I sound like when I'm frustrated. If you want more information, check out my
[blog post](https://elisstaaf.github.io/projects/2025/01/04/worst-language-sequel.html)
about this language.

## Install
There are two different implementations of brainfuck.
One old one, (you'll see that one if you read my blog post)
and one newer one.
```sh
git clone https://github.com/ElisStaaf/scream
cd scream

cd scream         # Blog post implementation
cd scream25       # The great '25 revision

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
