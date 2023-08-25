package eos.stiffenedgas;

service caseoption StiffenedGas implements eos.EquationOfState {

    /*! Définition de la tension limite */
    opt Real tension_limit_cst = "0.01";

    override eos.EquationOfState.initEOS
        in mahyco.pressure, in mahyco.density,
        out mahyco.internal_energy, out mahyco.sound_speed;

    override eos.EquationOfState.applyEOS
        in mahyco.internal_energy, in mahyco.density,
        out mahyco.pressure, out mahyco.sound_speed, out mahyco.dpde;

    override eos.EquationOfState.applyOneCellEOS
        in mahyco.internal_energy, in mahyco.density,
        out mahyco.pressure, out mahyco.sound_speed, out mahyco.dpde;
}