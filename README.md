<div align="center">

# ESP32 WEB GPIO CONTROL

</div>

## Folder contents

The project **esp32-web-gpio-control-espidf** contains one source main file in C language [main.c](main/main.c). The file is located in folder [main](main).

This project based on esp32 tutorial [here](https://esp32tutorials.com/esp32-esp-idf-spiffs-web-server/).

This ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── include
│   ├── connect_wifi.h
│   └──  http_server.h
├── main
│   ├── CMakeLists.txt
│   ├── connect_wifi.c
│   ├── http_server.c
│   ├── Kconfig.projbuild
│   └── main.c
├── spiffs_data
│   └── index.html
└── README.md                  This is the file you are currently reading
```