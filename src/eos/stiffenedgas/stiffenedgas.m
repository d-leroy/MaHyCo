package eos.stiffenedgas;

service caseoption StiffenedGas implements eos.EquationOfState {

    /*! Définition de la tension limite */
    [0..1] real TensionLimitCst = "0.01";

    override eos.EquationOfState.initEOS
        in mahyco.pressure, mahyco.density
        out mahyco.internal_energy, mahyco.sound_speed;

    override eos.EquationOfState.applyEOS
        in mahyco.internal_energy, mahyco.density
        out mahyco.pressure, mahyco.sound_speed, mahyco.dpde;

    override eos.EquationOfState.applyOneCellEOS
        in mahyco.internal_energy, mahyco.density
        out mahyco.pressure, mahyco.sound_speed, mahyco.dpde;
}