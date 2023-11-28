import scihook as sh
import arcpy
import numpy as np
import mahyco.eos_perfectgas_perfectgas as pg

@sh.register("PerfectGas.ApplyEOS.Before")
def log(ctx):
    density = np.array(ctx.density.global_variable, copy=False)
    internal_energy = np.array(ctx.internal_energy.global_variable, copy=False)
    print("=======BEFORE EOS=======")
    print(f"Density: {density[::100]}")
    print(f"Internal Energy: {internal_energy[::100]}")
    print(f"Median Density: {np.median(density):e}")
    print(f"Median Internal Energy: {np.median(internal_energy):e}")

@sh.register("PerfectGas.ApplyEOS.After")
def log(ctx):
    pressure = np.array(ctx.pressure.global_variable, copy=False)
    dpde = np.array(ctx.dpde.global_variable, copy=False)
    sound_speed = np.array(ctx.sound_speed.global_variable, copy=False)
    print("=======AFTER EOS=======")
    print(f"Pressure: {pressure[::100]}")
    print(f"DpDe: {dpde[::100]}")
    print(f"Sound Speed: {sound_speed[::100]}")
    print(f"Median Pressure: {np.median(pressure):e}")
    print(f"Median DpDe: {np.median(dpde):e}")
    print(f"Median Sound Speed: {np.median(sound_speed):e}")
