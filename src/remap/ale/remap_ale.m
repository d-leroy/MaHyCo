package remap.ale;

// TODO
service caseoption RemapALE implements remap.Remap {
    /*! Définition de la valeur limite des petites fractions et autres */
    Real Threshold="1.e-10";
    /*! Critere de remaillage d'un noeud sur le rapport du volume min et max des elements entourant ce noeud */
    Real VolumCriteria="1.";
    /*! Critere de remaillage d'un noeud sur le sinus des angles de l'élément */
    Real AngleCriteria="-1.";
    /*! Nombre d'itération de lissage du maillage */
    Int NbIterationWinslow="3";
    /*!  projection type Euler (retour sur maillage initial) */
    Bool IsEulerScheme="false";
    /*! Définition de la valeur limite des petites fractions et autres */
    Int OrdreProjection="2";
    /*! Conservation de l energie totale lors de la projection */
    Bool ConservationEnergieTotale="false";
    /*!  projection pente borne en volume dans les mailles mixtes et en masse dans les mailles pures */
    Bool ProjectionPenteBorneMixte="false";
    /*!  identifiant du limiteur pour les mailles mixtes */
    Int ProjectionLimiteurId="0";
    /*!  identifiant du limiteur pour les mailles pures */
    Int ProjectionLimiteurPureId="0";
    /*!  projection avec l'algorithme pente-borne */
    Bool ProjectionPenteBorne="false";
    /*!  projection avec l'algorithme pente-borne en evitant l'artefact de debar avec la valeur moyenne (1) ou valeur aux mailles (2) */
    Int ProjectionPenteBorneDebarFix="0";
    /*!  identifiant de la methode de projection duale */
    Int ProjectionDual="0";

    
}