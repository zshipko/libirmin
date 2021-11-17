from setuptools import setup
from distutils.command.build import build as _build
import subprocess
import platform


class build(_build):
    def run(self):
        subprocess.call(['make'])
        _build.run(self)


def with_shared_object_ext(base):
    if platform.system() == "Darwin":
        return base + ".dylib"
    return base + ".so"


setup(name='irmin',
      version='0.1',
      description='Irmin bindings for Python',
      author='Zach Shipko',
      author_email='zachshipko@gmail.com',
      url='https://github.com/zshipko/libirmin',
      packages=['irmin'],
      package_dir={'': 'py'},
      package_data={'': [with_shared_object_ext('./libirmin'), './irmin.h']},
      install_requires=["cffi>=1.0.0"],
      include_package_data=True,
      cmdclass={'build': build})
