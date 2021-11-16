from setuptools import setup

setup(
    name='irmin',
    version='0.1',
    description='Irmin bindings for Python',
    author='Zach Shipko',
    author_email='zachshipko@gmail.com',
    url='https://github.com/zshipko/libirmin',
    packages=['irmin'],
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["irmin/irmin_ffi.py:ffi"],
    install_requires=["cffi>=1.0.0"],
)
