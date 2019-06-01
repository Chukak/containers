astyle --indent=tab=4 --indent-col1-comments \
       --pad-oper --pad-comma --pad-header --add-braces --align-pointer=middle \
       --align-reference=type --close-templates \
       --recursive ./src/*.cpp,*h --recursive ./include/*.cpp,*.h --recursive ./tests/*.cpp,*h --recursive ./tests/performance/*.cpp,*.h
