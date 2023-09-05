import ctypes
import os

if os.name == 'nt':
    cpplib_path = os.path.join("bin", "Release", "app_lib.dll")
else:
    cpplib_path = os.path.join("bin", "libapp_lib.so")

cpplib = ctypes.CDLL(cpplib_path)

cpplib.main()


