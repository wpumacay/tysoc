#pragma once

#include <loco_data.h>
#include <primitives/loco_single_body.h>
#include <primitives/loco_single_body_collider_adapter.h>
#include <visualizer/loco_visualizer_drawable_adapter.h>

namespace loco
{
    class TSingleBody;
    class TISingleBodyColliderAdapter;

    class TSingleBodyCollider : public TObject
    {

    public :

        TSingleBodyCollider( const std::string& name,
                             const TCollisionData& collisionData );

        ~TSingleBodyCollider();

        void SetParentBody( TSingleBody* parent_body_ref );

        void SetColliderAdapter( TISingleBodyColliderAdapter* collider_adapter_ref );

        void SetDrawableAdapter( TIDrawableAdapter* drawable_adapter_ref );

        void SetVisible( bool visible );

        void SetWireframe( bool wireframe );

        void ChangeSize( const TVec3& new_size );

        void ChangeElevationData( const std::vector< float >& heights );

        void ChangeCollisionGroup( int collision_group );

        void ChangeCollisionMask( int collision_mask );

        eShapeType shape() const { return m_Data.type; }

        TVec3 size() const { return m_Data.size; }

        int collisionGroup() const { return m_Data.collisionGroup; }

        int collisionMask() const { return m_Data.collisionMask; }

        bool visible() const { return m_Visible; }

        bool wireframe() const { return m_Wireframe; }

        TCollisionData& data() { return m_Data; }

        const TCollisionData& data() const { return m_Data; }

        eObjectType GetObjectType() const override { return eObjectType::COLLIDER; }

        static eObjectType GetStaticType() { return eObjectType::COLLIDER; }

        TSingleBody* parent() { return m_ParentBodyRef; }

        const TSingleBody* parent() const { return m_ParentBodyRef; }

        TISingleBodyColliderAdapter* collider_adapter() { return m_ColliderAdapterRef; }

        const TISingleBodyColliderAdapter* collider_adapter() const { return m_ColliderAdapterRef; }

        TIDrawableAdapter* drawable_adapter() { return m_DrawableAdapterRef; }

        const TIDrawableAdapter* drawable_adapter() const { return m_DrawableAdapterRef; }

    protected :

        void _InitializeInternal() override;

        void _PreStepInternal() override;

        void _PostStepInternal() override;

        void _ResetInternal() override;

        void _DetachSimInternal() override;

        void _DetachVizInternal() override;

        void _SetTransformInternal( const TMat4& transform ) override;

    protected :

        // Construction data of this collider object
        TCollisionData m_Data;
        // Reference to the parent-body of this collider object
        TSingleBody* m_ParentBodyRef;
        // Reference to the drawable resource used for visualization
        TIDrawableAdapter* m_DrawableAdapterRef;
        // Adapter object that gives access to the low-level API for a specific backend
        TISingleBodyColliderAdapter* m_ColliderAdapterRef;
        // Flag that indicates the collider's drawable visibility
        bool m_Visible;
        // Flag that indicates the collider's drawable wireframe-mode
        bool m_Wireframe;
    };
}