echo "$(tput setaf 3)$(date -u)$(tput setaf 0)" "$(tput setaf 6)Compilation started$(tput setaf 1)"

start=`date +%s`
gcc win32_gefs.cc -o ./out/main -lopengl32 -lgdi32
end=`date +%s`

echo "$(tput setaf 3)$(date -u)$(tput setaf 0)" "$(tput setaf 2)Compilation finished in $((end-start))s$(tput sgr 0)"