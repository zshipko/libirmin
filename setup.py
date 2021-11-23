from setuptools import setup
from distutils.command.build import build as _build
import subprocess


class build(_build):
    def run(self):
        subprocess.call(['make'])
        _build.run(self)


setup(name='irmin',
      version='0.1',
      description='Irmin bindings for Python',
      author='Zach Shipko',
      author_email='zachshipko@gmail.com',
      url='https://github.com/zshipko/libirmin',
      packages=['irmin'],
      package_dir={'': 'py'},
      package_data={'': ['./libirmin.so', './irmin.h']},
      install_requires=["cffi>=1.0.0"],
      include_package_data=True,
      cmdclass={'build': build})
