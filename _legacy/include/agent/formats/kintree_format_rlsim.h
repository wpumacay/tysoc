
#pragma once

// rlsim functionality
#include <utils/parsers/rlsim/rlsim.h>
// base agent functionality
#include <agent/agent_base.h>

namespace tysoc {

    class TAgent;

    /* Storage used while parsing the rlsim data into a kinematic tree */
    struct TRlsimParsingContext
    {
        // Agent being constructed with this context
        TAgent* agentPtr;
        // Data used to construct the agent
        rlsim::RlsimModel* modelDataPtr;
        // Storage for joints created using the hack for spherical ...
        // joints, consisting of creating 3 revolute per 1 spherical
        std::vector< rlsim::RlsimJoint* > hackSphericalJoints;
        // A helper dictionary to create default actuators
        std::map< std::string, rlsim::RlsimJoint* > jointNameToJointNodeMap;
    };

    /* Creates an agent from the given rlsim model */
    rlsim::RlsimModel* constructAgentFromModel( TAgent* agentPtr,
                                                rlsim::RlsimModel* modelDataPtr );

    /*************************************************************
    *   Helpers used to construct the components of the kintree  *
    **************************************************************/

    TKinTreeBody* _processNode( TRlsimParsingContext& context, 
                                rlsim::RlsimJoint* rlsimJointPtr, 
                                TKinTreeBody* parentKinBodyPtr );

    TKinTreeJoint* _processJointFromRlsim( TRlsimParsingContext& context, 
                                           rlsim::RlsimJoint* rlsimJointPtr );

    TKinTreeVisual* _processVisualFromRlsim( TRlsimParsingContext& context, 
                                             const rlsim::RlsimVisual& rlsimVisual );

    TKinTreeCollision* _processCollisionFromRlsim( TRlsimParsingContext& context, 
                                                   rlsim::RlsimBody* rlsimBodyPtr );

    void _constructDefaultActuators( TRlsimParsingContext& context );

    void _extractStandardSize( const std::string& shapeType,
                               const TVec3& srcSize,
                               TVec3& dstSize );

}