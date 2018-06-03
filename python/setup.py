#from distutils.core import setup, Extension
from setuptools import  Extension, setup
from setuptools.command.build_ext import build_ext


class BuildExt(build_ext):
    def build_extensions(self):
        self.compiler.compiler_so.remove('-Wstrict-prototypes')
        super(BuildExt, self).build_extensions()


setup(
    cmdclass={"build_ext": BuildExt},
    name="containers",
    version="1.0",
    description="",
    url="https://github.com/Chukak/containers",
    ext_modules=[
        Extension(
            "containers",
            ["../src/queue.cpp", "pyqueue.c", "python.c", ],
            include_dirs=["../src"],
            extra_compile_args=[
                "-g", "-lstdc++",  "-Wall", "-D_DEFAULT_SOURCE"
            ]
        ),
    ],
    py_modules=["containers"],
)
