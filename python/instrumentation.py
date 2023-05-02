import scihook as sh
import arcpy
import numpy as np

breakpoint_enabled = True

def printValue(v):
    print("{:e}".format(v))

@sh.register("PerfectGasServiceBase.ApplyEOS.Before")
def log(ctx):
    density = np.array(ctx.density.global_variable)
    internal_energy = np.array(ctx.internal_energy.global_variable)
    print("=======BEFORE EOS=======")
    print(density[::100])
    print(internal_energy[::100])
    printValue(np.median(density))
    printValue(np.median(internal_energy))

@sh.register("PerfectGasServiceBase.ApplyEOS.After")
def log(ctx):
    pressure = np.array(ctx.pressure.global_variable)
    dpde = np.array(ctx.dpde.global_variable)
    sound_speed = np.array(ctx.sound_speed.global_variable)
    print("=======AFTER EOS=======")
    print(pressure[::100])
    print(dpde[::100])
    print(sound_speed[::100])
    printValue(np.median(pressure))
    printValue(np.median(dpde))
    printValue(np.median(sound_speed))