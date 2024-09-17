set(LED_REPO_PATH ../../submodules/Pico_WS2812_c/)

add_library(led
    led.c
    ${LED_REPO_PATH}/src/WS2812.c
)

target_include_directories(led
    PUBLIC
        .
        ${LED_REPO_PATH}/src
    PRIVATE
)

target_link_libraries(led
    PUBLIC
        pico_stdlib
        hardware_pio
        hardware_dma
)

# Generate the header for the pio functionality
pico_generate_pio_header(led ${CMAKE_CURRENT_LIST_DIR}/${LED_REPO_PATH}/src/WS2812.pio)
