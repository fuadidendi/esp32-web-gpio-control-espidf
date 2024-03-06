set(srcs    "main.c"
            "connect_wifi.c"
            "http_server.c"
	    )
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "../include")
spiffs_create_partition_image(storage ../spiffs_data FLASH_IN_PROJECT)