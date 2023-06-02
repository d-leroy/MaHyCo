package types_mahyco;

struct Material {
    /*! Nom du materiau */
    String name;
}

struct Environment {
    /*! Nom du milieu */
    String name;
    /*! Nom du materiau */
    String[*] material;
    /*! Service d'equation d'état */
    eos.EquationOfState EosModel;
}

struct BoundaryCondition {
    /*! Type de condition aux limites */
    BoundaryConditionType type;
    /*! Surface sur laquelle s'applique la condition aux limites */
    String surface;
    /*! Valeur de la composante à fixer */
    Real value;
}

enum BoundaryConditionType {
    Vx; Vy; Vz;
}

legacy IGeometryMng file "arcane/geometry/IGeometryMng.h" namespace "Arcane::Numerics";
legacy IMeshEnvironment file "arcane/materials/IMeshEnvironment.h" namespace "Arcane::Materials";
