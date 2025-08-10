#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
BOLD='\033[1m'
DIM='\033[2m'
NC='\033[0m'

SPINNER_FRAMES=("⠋" "⠙" "⠹" "⠸" "⠼" "⠴" "⠦" "⠧" "⠇" "⠏")

show_progress() {
    local current=$1
    local total=$2
    local message=$3
    local width=50
    local percentage=$((current * 100 / total))
    local filled=$((current * width / total))
    
    printf "\r${CYAN}[${NC}"
    for ((i=0; i<filled; i++)); do printf "${GREEN}█${NC}"; done
    for ((i=filled; i<width; i++)); do printf "${DIM}░${NC}"; done
    printf "${CYAN}]${NC} ${WHITE}%3d%%${NC} ${message}" $percentage
}

spinner() {
    local pid=$1
    local message=$2
    local i=0
    
    while kill -0 $pid 2>/dev/null; do
        printf "\r${CYAN}${SPINNER_FRAMES[i]}${NC} ${message}"
        i=$(((i+1) % ${#SPINNER_FRAMES[@]}))
        sleep 0.1
    done
    printf "\r${GREEN}✓${NC} ${message}"
}

run() {
    local cmd="$*"
    echo -e "${BLUE}❯${NC} ${DIM}${cmd}${NC}"
    
    $cmd > /dev/null 2>&1 &
    local pid=$!
    spinner $pid "Executing"
    
    wait $pid
    local exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        echo -e "\n${RED}✗ Failed:${NC} ${cmd}"
        echo -e "${RED}Exit code:${NC} $exit_code"
        exit $exit_code
    fi
    
    echo
    return 0
}

run_silent() {
    local cmd="$*"
    $cmd > /dev/null 2>&1
    local exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}✗ Failed:${NC} ${cmd}"
        exit $exit_code
    fi
    
    return 0
}

show_help() {
    echo -e "${CYAN}Usage: $0 [OPTIONS]${NC}"
    echo
    echo -e "${CYAN}OPTIONS:${NC}"
    echo -e "  ${GREEN}--build${NC},   ${GREEN}-b${NC}   ${WHITE}Compiles the project${NC}"
    echo -e "  ${GREEN}--run${NC},     ${GREEN}-r${NC}   ${WHITE}Compiles and runs executables${NC}"
    echo -e "  ${GREEN}--install${NC}, ${GREEN}-i${NC}   ${WHITE}Compiles and installs executable${NC}"
    echo -e "  ${GREEN}--termux${NC},  ${GREEN}-t${NC}   ${WHITE}Compiles fixing termux problems${NC}"
    echo -e "  ${GREEN}--asan${NC},    ${GREEN}-as${NC}  ${WHITE}Compiles with Address Sanitizer${NC}"
    echo -e "  ${GREEN}--gdb${NC},     ${GREEN}-g${NC}   ${WHITE}Run with GNU Debugger (with --run)${NC}"
    echo -e "  ${GREEN}--help${NC},    ${GREEN}-h${NC}   ${WHITE}Shows this help message${NC}"
    echo
}

option_build=false
option_termux=false
option_run=false
option_asan=false
option_gdb=false
option_install=false

if [ $# -eq 0 ]; then
    echo -e "${YELLOW}No arguments provided.${NC}"
    show_help
    exit 1
fi

for arg in "$@"; do
    case $arg in
        --build|-b)
            option_build=true
            ;;
        --termux|-t)
            option_termux=true
            ;;
        --run|-r)
            option_run=true
            ;;
        --asan|-as)
            option_asan=true
            ;;
        --gdb|-g)
            option_gdb=true
            ;;
        --install|-i)
            option_install=true
            ;;
        --help|-h)
            show_help
            exit 0
            ;;
        *)
            echo -e "${RED}Invalid argument:${NC} ${arg}"
            echo -e "${YELLOW}Use --help to see all available commands${NC}"
            exit 1
            ;;
    esac
done

if [ "$option_build" = true ]; then
    echo -e "${BOLD}${BLUE}Starting build process...${NC}"
    
    echo -e "${CYAN}Creating build directory...${NC}"
    mkdir -p build
    show_progress 1 4 "Build directory created"
    echo
    
    echo -e "${CYAN}Configuring cmake...${NC}"
    install_pr="${PREFIX:-/usr/local}"
    asan_flag=$([ "$option_asan" = true ] && echo "ON" || echo "OFF")
    
    cmake_cmd="cmake -B build -S . -DASAN=$asan_flag -DCMAKE_INSTALL_PREFIX=$install_pr"
    run "$cmake_cmd"
    show_progress 2 4 "CMake configuration completed"
    echo
    
    echo -e "${CYAN}Building project...${NC}"
    run "cmake --build build"
    show_progress 3 4 "Project build completed"
    echo
    
    show_progress 4 4 "Build process finished"
    echo
    echo -e "${GREEN}Build completed successfully${NC}"
    echo
fi

if [ "$option_install" = true ]; then
    echo -e "${BOLD}${MAGENTA}Installing...${NC}"
    run "cmake --install build"
    echo -e "${GREEN}Installation completed${NC}"
    echo
fi

if [ "$option_run" = true ]; then
    echo -e "${BOLD}${YELLOW}Running application...${NC}"
    
    args="test"
    
    if [ "$option_termux" != true ]; then
        echo -e "${CYAN}Setting executable permissions...${NC}"
        run_silent "chmod +x build/hate2d"
        
        if [ "$option_gdb" = true ]; then
            echo -e "${MAGENTA}Starting with GNU Debugger...${NC}"
            run "gdb ./build/hate2d --args ./build/hate2d $args"
        else
            echo -e "${GREEN}Executing hate2d...${NC}"
            run "./build/hate2d $args"
        fi
    else
        HOME_DIR="${HOME:-$PWD}"
        export DISPLAY=":0"
        
        echo -e "${CYAN}Setting up Termux environment...${NC}"
        mkdir -p "$HOME_DIR/temp/c/hate2d/"
        cp "build/hate2d" "$HOME_DIR/temp/c/hate2d/hate2d"
        
        EXECUTABLE="hate2d"
        
        echo -e "${YELLOW}Starting termux-x11...${NC}"
        termux-x11 :0 &
        x11_pid=$!
        
        cleanup() {
            echo -e "\n${YELLOW}Shutting down termux-x11...${NC}"
            kill $x11_pid 2>/dev/null
            exit 0
        }
        
        trap cleanup INT TERM
        
        echo -e "${DIM}Waiting for X11 server to start...${NC}"
        for i in {1..5}; do
            show_progress $i 5 "Initializing X11 server"
            sleep 1
        done
        echo
        
        exec_path="$HOME_DIR/temp/c/hate2d/$EXECUTABLE"
        chmod 755 "$exec_path"
        
        if [ "$option_gdb" = true ]; then
            echo -e "${MAGENTA}Starting with GNU Debugger...${NC}"
            gdb "$exec_path" --args "$exec_path" $args
        else
            echo -e "${GREEN}Executing hate2d...${NC}"
            "$exec_path" $args
        fi
        
        cleanup
    fi
fi

echo -e "${BOLD}${GREEN}All operations completed successfully${NC}"