package eos.perfectgas;

service caseoption PerfectGas implements eos.EquationOfState {
    /*!
     * Définition de la tension limite
     */
    opt Real limit_tension = "0.0";
    
    override eos.EquationOfState.initEOS
        in mahyco.pressure, in mahyco.density,
        out mahyco.internal_energy, out mahyco.sound_speed;

    override eos.EquationOfState.applyEOS
        in mahyco.density, in mahyco.internal_energy,
        out mahyco.pressure, out mahyco.sound_speed, out mahyco.dpde
        // call compute_pressure_sndspd_PG
        ;

    override eos.EquationOfState.applyOneCellEOS
        in mahyco.density, in mahyco.internal_energy,
        out mahyco.pressure, out mahyco.sound_speed, out mahyco.dpde
        // call compute_pressure_sndspd_PG
        ;

    // def void compute_pressure_sndspd_PG(
    //     in real adiabatic_cst, in real density, in real internal_energy,
    //     out real pressure, out real sound_speed, out real dpde);
}
