# Hate2D
- A Lua Framework inspired by LÖVE 2D

# Building from source

## Dependencies
> [!NOTE]
> If you don't have any of these deps, it will compile they automatically for you (expect for ruby), so don't worry.

- `Ruby` for buildscript.
- `gcc or clang` for building.
- `SDL3`
- `SDL3_ttf`
- `SDL3_image`
- `Lua 5.1`

## Build & Run
- Well, to build it, you just need to run this command below:

> [!TIP]
> Use --help to see all commands.

```bash
ruby build.rb --run
```

## Build & Install
- It will install the executable (`hate2d`) in `$PREFIX/usr/bin`
```bash
ruby build.rb --install
```
