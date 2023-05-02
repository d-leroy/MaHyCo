package cas_test;

interface Initialisations {
    /*! Numéro du cas test */
    Int casTest;
    /*! Option de retour arriere */
    Bool reverseOption = "false";
    /*! Parametre du cas test */
    Real parametre = "0.";

    def void initMatMono(in Int dim);
    def void initVarMono(in Int dim);
    def void initMat(in Int dim);
    def void initVar(in Int dim);
}
