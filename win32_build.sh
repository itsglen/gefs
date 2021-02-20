echo "$(tput setaf 3)$(date -u)$(tput setaf 0)" "$(tput setaf 6)Win32 Compilation started$(tput setaf 1)"

start=`date +%s`
gcc ./gefs/platforms/win32/win32_gefs.cc -o ./out/win32_gefs -std=c++11 -lopengl32 -lgdi32
end=`date +%s`

echo "$(tput setaf 3)$(date -u)$(tput setaf 0)" "$(tput setaf 2)Compilation finished in $((end-start))s$(tput sgr 0)"