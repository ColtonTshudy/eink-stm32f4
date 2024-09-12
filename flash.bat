cmake --build C:/Users/Tshud/Documents/GitHub/eink-stm32f4/build/Debug --

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg ^
    -c init ^
    -c "reset init" ^
    -c "program build/Debug/eink-stm32f4.elf" ^
    -c reset ^
    -c shutdown