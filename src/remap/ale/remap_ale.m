package remap::ale;

// TODO
service caseoption RemapALE implements remap::Remap {
    /*! Critere de remaillage d'un noeud sur le rapport du volume min et max des elements entourant ce noeud */
    Real volum_criteria="1.";
    /*! Critere de remaillage d'un noeud sur le sinus des angles de l'élément */
    Real angle_criteria="-1.";
    /*! Nombre d'itération de lissage du maillage */
    Int nb_iteration_winslow="3";
    /*!  identifiant de la methode de projection duale */
    Int projection_dual="0";

    override void appliRemap(in Int dimension, in Int withDualProjection, in Int nb_vars_to_project, in Int nb_env);
    
    override void resizeRemapVariables(in Int nb_vars_to_project, in Int nb_env);
    
    override void synchronizeUremap();
    
    override void remapVariables(in Int dimension, in Int withDualProjection, in Int nb_vars_to_project, in Int nb_env);
}
