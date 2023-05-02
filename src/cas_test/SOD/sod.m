package cas_test.SOD;

service caseoption Sod implements cas_test.Initialisations {
    override cas_test.Initialisations.initMatMono;
    override cas_test.Initialisations.initVarMono;
    override cas_test.Initialisations.initMat;
    override cas_test.Initialisations.initVar;
}
