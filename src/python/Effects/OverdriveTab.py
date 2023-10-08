import sys
sys.path.append("..")
from Effect import Effect

class OverdriveTab(Effect):
    def __init__(self, effectPtr, cpplib):
        Effect.__init__(self, effectPtr, cpplib)



