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
    eos::EquationOfState eos_model;
}

struct BoundaryCondition {
    /*! Type de condition aux limites */
    BoundaryConditionType type;
    /*! Surface sur laquelle s'applique la condition aux limites */
    String surface;
    /*! Valeur de la composante à fixer */
    Real value;


    // NodeGroup nodes; //!< le groupe de noeuds sur lequel s'applique la CL
    // NodeVectorView boundary_nodes; //!< vue relative à ce groupe de noeuds
    // Real value; //!< la valeur appliquée à la composante de vitesse
    // TypesMahyco::eBoundaryCondition type; //!< le type de CL

}

enum BoundaryConditionType {
    Vx; Vy; Vz; Unknown;
}

enum Limiteur {
    Minmod;
    SuperBee;
    VanLeer;
    MinmodG;
    SuperBeeG;
    VanLeerG;
    ArithmeticG;
    UltrabeeG;
}

legacy IGeometryMng file "arcane/geometry/IGeometryMng.h" namespace "Arcane::Numerics";
legacy IMeshEnvironment file "arcane/materials/IMeshEnvironment.h" namespace "Arcane::Materials";
legacy SingletonIAccEnv file "accenv/SingletonIAccEnv.h" namespace "";
legacy ICartesianMesh file "cartesian/interface/ICartesianMesh.h" namespace "CartesianInterface";
legacy RealArrayView file "arcane/utils/UtilsTypes.h" namespace "Arcane";
// TODO: template types
// legacy DtCellInfoVoid file "types_mahyco/IDtCellInfo.h" namespace "";