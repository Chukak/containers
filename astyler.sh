astyle --indent=tab=4 --indent-namespaces \
       --indent-preproc-block --indent-preproc-define --indent-col1-comments \
       --pad-oper --pad-comma --pad-header --add-braces --align-pointer=middle \
       --align-reference=type --max-code-length=160 --close-templates \
       --attach-return-type --attach-return-type-decl \
       --recursive ./src/*.cpp,*.h
