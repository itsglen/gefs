echo "$(tput setaf 3)$(date -u)$(tput setaf 0)" "$(tput setaf 6)GLFW Compilation started$(tput setaf 1)"

start=`date +%s`
gcc ./gefs/platforms/glfw/glfw_gefs.cc -o ./out/glfw_gefs -std=c++11 -lGdi32 -lUser32 -lShell32 -lopengl32 -lglew32 -lglfw3
end=`date +%s`

echo "$(tput setaf 3)$(date -u)$(tput setaf 0)" "$(tput setaf 2)Compilation finished in $((end-start))s$(tput sgr 0)"