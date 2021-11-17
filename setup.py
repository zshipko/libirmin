from setuptools import setup

from distutils.command.install import install as _install
from distutils.command.build import build as _build
import subprocess
import platform


class build(_build):
    def run(self):
        subprocess.call(['make'])
        _build.run(self)


class install(_install):
    def run(self):
        subprocess.call(['make'])
        _install.run(self)


def with_shared_object_ext(base):
    if platform.system() == "Darwin":
        return base + ".dylib"
    return base + ".so"


setup(
    name='irmin',
    version='0.1',
    description='Irmin bindings for Python',
    author='Zach Shipko',
    author_email='zachshipko@gmail.com',
    url='https://github.com/zshipko/libirmin',
    packages=['py/irmin'],
    package_data={'py/irmin': [with_shared_object_ext('./libirmin')]},
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["py/irmin/irmin_ffi.py:ffi"],
    install_requires=["cffi>=1.0.0"],
    cmdclass={
        'build': build,
        'install': install
    },
)
