package remap.ale;

// TODO
service caseoption RemapALE implements remap.Remap {
    /*! Critere de remaillage d'un noeud sur le rapport du volume min et max des elements entourant ce noeud */
    Real VolumCriteria="1.";
    /*! Critere de remaillage d'un noeud sur le sinus des angles de l'élément */
    Real AngleCriteria="-1.";
    /*! Nombre d'itération de lissage du maillage */
    Int NbIterationWinslow="3";
    /*!  identifiant de la methode de projection duale */
    Int ProjectionDual="0";    
}
