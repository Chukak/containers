import sys
import os
from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext


class BuildExt(build_ext):
    def build_extensions(self):
        self.compiler.compiler_so.remove('-Wstrict-prototypes')
        super(BuildExt, self).build_extensions()


if __name__ == "__main__":
    one, two = sys.version_info[0], sys.version_info[1]
    if os.environ.get("PY_HEADER_PATH", ""):
        paths = [
            str(os.environ["PY_HEADER_PATH"]),
            "../src"
        ]
    else:
        paths = [
            "/usr/include/python" + str(one) + "." + str(two),
            "/usr/local/include/python" + str(one) + "." + str(two),
            "/usr/lib/python" + str(one) + "." + str(two),
            "/usr/local/lib/python" + str(one) + "." + str(two),
            "../src"
        ]
    os.environ["PY_HEADER_PATH"] = ""
    setup(
        cmdclass={"build_ext": BuildExt},
        name="containers",
        version="1.0",
        description="",
        url="https://github.com/Chukak/containers",
        ext_modules=[
            Extension(
                "containers",
                ["../src/queue.cpp", "pyqueue.c", "../src/stack.cpp", "pystack.c", "python.c", ],
                include_dirs=paths,
                extra_compile_args=[
                    "-g", "-Werror", "-Wall"
                ],
            ),
        ],
        py_modules=["containers"],
    )
