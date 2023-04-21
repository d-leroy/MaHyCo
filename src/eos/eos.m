package eos;

interface EquationOfState {
    /*! Définition de la constante adiabatique */
    [1..1] real AdiabaticCst = "1.4";
    /*! 
     *  Initialise l'équation d'état au groupe de mailles passé en argument
     *  et calcule la vitesse du son et l'énergie interne. 
     */
    // TODO: passer en in quand les méthodes de IMeshEnvironment deviendront const
    def void initEOS(inout arcane_legacy.IMeshEnvironment env);
    /*! 
     *  Applique l'équation d'état au groupe de mailles passé en argument
     *  et calcule la vitesse du son et la pression. 
     */
    // TODO: passer en in quand les méthodes de IMeshEnvironment deviendront const
    def void applyEOS(inout arcane_legacy.IMeshEnvironment env);
    /*! 
     *  Applique l'équation d'état au groupe de mailles passé en argument
     *  et calcule la vitesse du son et la pression pour une cellule
     */
    def void applyOneCellEOS(in arcane_legacy.IMeshEnvironment env, in envCell ev);
}
