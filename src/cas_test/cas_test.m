package cas_test;

enum Test {
    // cas test
     UnitTestCase = 0;
     Sedov = 1;
     TriplePoint = 2;
     SodCaseX = 3;
     SodCaseY = 4;
     SodCaseZ = 5;
     NohTestCase = 6;
     AdvectionX = 7;
     AdvectionY = 8;
     AdvectionVitX = 9;
     AdvectionVitY = 10;
     BiSedov = 11;
     BiTriplePoint = 12;
     BiSodCaseX = 13;
     BiSodCaseY = 14;
     BiSodCaseZ = 15;
     BiShockBubble = 16;
     BiNohTestCase = 17;
     BiAdvectionX = 18;
     BiAdvectionY = 19;
     BiAdvectionVitX = 20;
     BiAdvectionVitY = 21;
     BiImplosion = 22;
     MonoRiderTx = 23;
     MonoRiderTy = 24;
     MonoRiderT45 = 25;
     MonoRiderRotation = 26;
     MonoRiderVortex = 27;
     MonoRiderDeformation = 28;
     MonoRiderVortexTimeReverse = 29;
     MonoRiderDeformationTimeReverse = 30;
     RiderTx = 31;
     RiderTy = 32;
     RiderT45 = 33;
     RiderRotation = 34;
     RiderVortex = 35;
     RiderDeformation = 36;
     RiderVortexTimeReverse = 37;
     RiderDeformationTimeReverse = 38;
     BiSodSph = 39;
}

interface Initialisations {
    /*! Numéro du cas test */
    Test casTest;
    /*! Option de retour arriere */
    opt Bool reverseOption = "false";
    /*! Parametre du cas test */
    Real parameter = "0.";

    def void initMatMono(in Int dim);
    def void initVarMono(in Int dim);
    def void initMat(in Int dim);
    def void initVar(in Int dim);
}
