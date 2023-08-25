package eos;

interface EquationOfState {
    /*! Définition de la constante adiabatique */
    Real adiabatic_cst = "1.4";
    /*! 
     *  Initialise l'équation d'état au groupe de mailles passé en argument
     *  et calcule la vitesse du son et l'énergie interne. 
     */
    // TODO: passer en in quand les méthodes de IMeshEnvironment deviendront const
    def void initEOS(inout types_mahyco.IMeshEnvironment env);
    /*! 
     *  Applique l'équation d'état au groupe de mailles passé en argument
     *  et calcule la vitesse du son et la pression. 
     */
    // TODO: passer en in quand les méthodes de IMeshEnvironment deviendront const
    def void applyEOS(inout types_mahyco.IMeshEnvironment env);
    /*! 
     *  Applique l'équation d'état au groupe de mailles passé en argument
     *  et calcule la vitesse du son et la pression pour une cellule
     */
    def void applyOneCellEOS(in types_mahyco.IMeshEnvironment env, in EnvCell ev);
}
