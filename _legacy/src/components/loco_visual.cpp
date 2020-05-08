
#include <components/loco_visual.h>

namespace loco
{
    TVisual::TVisual( const std::string& name,
                      const TVisualData& visualData )
    {
        m_name = name;
        m_data = visualData;
        m_localTf = m_data.localTransform;
        m_visible = true;
        m_wireframe = false;

        m_parentBodyRef = nullptr;
        m_drawableImplRef = nullptr;

        #if defined( LOCO_CORE_USE_TRACK_ALLOCS )
            if ( tinyutils::Logger::IsActive() )
                LOCO_CORE_TRACE( "Loco::Allocs: Created TVisual {0} @ {1}", m_name, tinyutils::PointerToHexAddress( this ) );
            else
                std::cout << "Loco::Allocs: Created TVisual " << m_name << " @ " << tinyutils::PointerToHexAddress( this ) << std::endl;
        #endif
    }

    TVisual::~TVisual()
    {
        m_parentBodyRef = nullptr;
        m_drawableImplRef = nullptr;

        #if defined( LOCO_CORE_USE_TRACK_ALLOCS )
            if ( tinyutils::Logger::IsActive() )
                LOCO_CORE_TRACE( "Loco::Allocs: Destroyed TVisual {0} @ {1}", m_name, tinyutils::PointerToHexAddress( this ) );
            else
                std::cout << "Loco::Allocs: Destroyed TVisual " << m_name << " @ " << tinyutils::PointerToHexAddress( this ) << std::endl;
        #endif
    }

    void TVisual::SetParentBody( TIBody* parentBodyRef )
    {
        if ( !parentBodyRef )
            return;

        m_parentBodyRef = parentBodyRef;
        m_tf = m_parentBodyRef->tf() * m_localTf;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetWorldTransform( m_tf );
    }

    void TVisual::SetDrawable( TIDrawable* drawableImplRef )
    {
        if ( !drawableImplRef )
            return;

        m_drawableImplRef = drawableImplRef;
        m_drawableImplRef->SetWorldTransform( m_tf );
    }

    void TVisual::SetVisible( bool visible )
    {
        m_visible = visible;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetVisible( visible );
    }

    void TVisual::SetWireframe( bool wireframe )
    {
        m_wireframe = wireframe;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetWireframe( wireframe );
    }

    void TVisual::Initialize()
    {
        // Nothing extra to initialize (for now)
    }

    void TVisual::PreStep()
    {
        // Not much to do before a simulation step (for now)
    }

    void TVisual::PostStep()
    {
        // Update our own transform using the world-transform from the parent
        if ( m_parentBodyRef )
            m_tf = m_parentBodyRef->tf() * m_localTf;

        // Set the transform of the renderable to be our own world-transform
        if ( m_drawableImplRef )
            m_drawableImplRef->SetWorldTransform( m_tf );
    }

    void TVisual::Reset()
    {
        // Nothing extra to reset (for now)
    }

    void TVisual::Detach()
    {
////         if ( m_drawableImplRef )
////             m_drawableImplRef->OnDetach();
//// 
////         m_drawableImplRef = nullptr;
    }

    void TVisual::SetLocalPosition( const TVec3& localPosition )
    {
        m_localTf.set( localPosition, 3 );
    }

    void TVisual::SetLocalRotation( const TMat3& localRotation )
    {
        m_localTf.set( localRotation );
    }

    void TVisual::SetLocalQuat( const TVec4& localQuaternion )
    {
        auto localRotation = tinymath::rotation( localQuaternion );
        m_localTf.set( localRotation );
    }

    void TVisual::SetLocalEuler( const TVec3& localEuler )
    {
        auto localRotation = tinymath::rotation( localEuler );
        m_localTf.set( localRotation );
    }

    void TVisual::SetLocalTransform( const TMat4& localTransform )
    {
        m_localTf = localTransform;
    }

    void TVisual::ChangeSize( const TVec3& newSize )
    {
        // Change the visual-data size property
        m_data.size = newSize;

        // Set the new size of the drawable resource
        if ( m_drawableImplRef )
            m_drawableImplRef->ChangeSize( newSize );
    }

    void TVisual::ChangeElevationData( const std::vector< float >& heights )
    {
        if ( m_data.type != eShapeType::HFIELD )
        {
            LOCO_CORE_WARN( "TVisual::ChangeElevationData >>> collision shape {0} is not a hfield", m_name );
            return;
        }

        auto& hfield_data = m_data.hfield_data;
        // sanity check: make sure that both internal and given buffers have same num-elements
        if( ( hfield_data.nWidthSamples * hfield_data.nDepthSamples ) != heights.size() )
        {
            LOCO_CORE_WARN( "TVisual::ChangeElevationData >>> given buffer doesn't match expected size of collision shape {0}", m_name );
            LOCO_CORE_WARN( "\tnx-samples    : {0}", hfield_data.nWidthSamples );
            LOCO_CORE_WARN( "\tny-samples    : {0}", hfield_data.nDepthSamples );
            LOCO_CORE_WARN( "\tinternal-size : {0}", ( hfield_data.nWidthSamples * hfield_data.nDepthSamples ) );
            LOCO_CORE_WARN( "\tgiven-size    : {0}", heights.size() );
            return;
        }

        // Change the internal elevation data
        hfield_data.heights = heights;

        // Set the new elevation data of the drawable resource
        if ( m_drawableImplRef )
            m_drawableImplRef->ChangeElevationData( heights );
    }

    void TVisual::ChangeColor( const TVec3& newFullColor )
    {
        m_data.ambient = newFullColor;
        m_data.diffuse = newFullColor;
        m_data.specular = newFullColor;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetColor( newFullColor );
    }

    void TVisual::ChangeAmbientColor( const TVec3& newAmbientColor )
    {
        m_data.ambient = newAmbientColor;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetAmbientColor( newAmbientColor );
    }

    void TVisual::ChangeDiffuseColor( const TVec3& newDiffuseColor )
    {
        m_data.diffuse = newDiffuseColor;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetDiffuseColor( newDiffuseColor );
    }

    void TVisual::ChangeSpecularColor( const TVec3& newSpecularColor )
    {
        m_data.specular = newSpecularColor;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetSpecularColor( newSpecularColor );
    }

    void TVisual::ChangeShininess( const TScalar& shininess )
    {
        m_data.shininess = shininess;

        if ( m_drawableImplRef )
            m_drawableImplRef->SetShininess( shininess );
    }
}