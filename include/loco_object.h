#pragma once

#include <loco_math.h>

namespace loco 
{
    enum class eObjectType
    {
        BASE = 0,
        COLLIDER,
        VISUAL,
        SINGLE_BODY
    };

    class TObject
    {
    public :

        TObject( const std::string& name )
            : m_name( name ) {};

        virtual ~TObject() = default;

        void Initialize();

        void PreStep();

        void PostStep();

        void Reset();

        void DetachSim();

        void DetachViz();

        void SetPosition( const TVec3& position );

        void SetRotation( const TMat3& rotation );

        void SetEuler( const TVec3& euler );

        void SetQuaternion( const TVec4& quaternion );

        void SetTransform( const TMat4& transform );

        TVec3 pos() const { return TVec3( m_tf.col( 3 ) ); }

        TMat3 rot() const { return TMat3( m_tf ); }

        TVec3 euler() const { return tinymath::euler( m_tf ); }

        TVec4 quat() const { return tinymath::quaternion( m_tf ); }

        TMat4 tf() const { return m_tf; }

        std::string name() const { return m_name; }

        virtual eObjectType GetObjectType() const { return eObjectType::BASE; }

        static eObjectType GetStaticType() { return eObjectType::BASE; }

    protected :

        virtual void _InitializeInternal() = 0;

        virtual void _PreStepInternal() = 0;

        virtual void _PostStepInternal() = 0;

        virtual void _ResetInternal() = 0;

        virtual void _DetachSimInternal() = 0;

        virtual void _DetachVizInternal() = 0;

        virtual void _SetTransformInternal( const TMat4& transform ) = 0;

    protected :

        // Unique identifier of the object in the scenario
        std::string m_name;
        // World transform of the object in the scenario
        TMat4 m_tf;
    };
}