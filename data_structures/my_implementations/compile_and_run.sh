if [ -z "$1" ]; then
    echo "Usage: compile_and_run <filename>"
    return 1
fi

g++ -std=c++20 "$1.cpp" -o "$1.out" && ./"$1.out" && rm "$1.out"
