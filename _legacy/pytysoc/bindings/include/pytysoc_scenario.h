#pragma once

#include <scenario.h>
#include <pytysoc_common.h>
#include <pytysoc_single_body.h>
#include <pytysoc_compound.h>
#include <pytysoc_agent_core.h>
#include <pytysoc_terrainGen.h>
#include <pytysoc_sensors.h>

namespace py = pybind11;

namespace pytysoc
{

    class PyScenario
    {

        private :

        tysoc::TScenario* m_scenarioPtr;

        std::vector< PySingleBody* > m_pySingleBodies;
        std::vector< PyCompound* > m_pyCompounds;
        std::vector< PyCoreAgent* > m_pyCoreAgents;
        std::vector< PySensor* > m_pySensors;
        std::vector< PyTerrainGen* > m_pyTerrainGens;

        std::map< std::string, PySingleBody* > m_pySingleBodiesMap;
        std::map< std::string, PyCompound* > m_pyCompoundsMap;
        std::map< std::string, PyCoreAgent* > m_pyCoreAgentsMap;
        std::map< std::string, PySensor* > m_pySensorsMap;
        std::map< std::string, PyTerrainGen* > m_pyTerrainGensMap;

        public :
        
        /**
        *   Creates a wrapper for a tysoc::TScenario object. This wrapper ...
        *   is intended to be used along other wrappers (python bindings) ...
        *   like PyCoreAgent, PyCoreTerrainGen, and PyCoreSensor to assemble ...
        *   a scenario in a similar way to the C/C++ way of constructing a ...
        *   scenario from scratch, and then use it when instantiating a runtime.
        *
        *   @exposed    Exposed through python API
        */
        PyScenario();

        /**
        *   Destructor for this wrapper. In a similar way to the C/C++ API ...
        *   this scenario wrapper is intended to have ownership of the agents, ...
        *   terraingens and sensors, so we delete these resources when deleting ...
        *   this scenario.
        */
        ~PyScenario();

        /**
        *   Adds a single-body PySingleBody wrapper to this scenario wrapper
        *
        *   @param pySingleBodyRef  A pointer to the PySingleBody wrapper to be added
        *   @exposed                Exposed through python API
        */
        void addSingleBody( PySingleBody* pySingleBodyRef );

        /**
        *   Adds a single-body PySingleBody wrapper to this scenario wrapper
        *
        *   @param pyCompoundRef    A pointer to the pyCompoundRef wrapper to be added
        *   @exposed                Exposed through python API
        */
        void addCompound( PyCompound* pyCompoundRef );

        /**
        *   Adds a PyCoreAgent wrapper to this scenario wrapper
        *
        *   @param pyCoreAgentPtr   A pointer to the PyCoreAgent wrapper to add to the scenario
        *   @exposed                Exposed through python API
        */
        void addAgent( PyCoreAgent* pyCoreAgentPtr );

        /**
        *   Adds a PyTerrainGen wrapper to this scenario wrapper
        *
        *   @param pyTerrainGenPtr      A pointer to the PyTerrainGen wrapper to add to the scenario
        *   @exposed                    Exposed through python API
        */
        void addTerrainGen( PyTerrainGen* pyTerrainGenPtr );

        /**
        *   Adds a PySensor wrapper to this scenario wrapper
        *
        *   @param pySensorPtr      A pointer to the PySensor wrapper to add to the scenario
        *   @exposed                Exposed through python API
        */
        void addSensor( PySensor* pySensorPtr );

        /**
        *   Gets the single-body PySingleBody wrapper of a single-body in the scenario with a given name
        *
        *   @param name     The name of the wrapped single-body ther user has requested
        *   @exposed        Exposed through python API
        */
        PySingleBody* getSingleBodyByName( const std::string& name );

        /**
        *   Gets the compound-body pyCompoundRef wrapper of a compound-body in the scenario with a given name
        *
        *   @param name     The name of the wrapped compound-body ther user has requested
        *   @exposed        Exposed through python API
        */
        PyCompound* getCompoundByName( const std::string& name );

        /**
        *   Gets the PyCoreAgent wrapper of an agent with a given name
        *   
        *   @param name     The name of the wrapped agent the user requests
        *   @exposed        Exposed through python API
        */
        PyCoreAgent* getAgentByName( const std::string& name );

        /**
        *   Gets the PyTerrainGen wrapper of a terrainGen with a given name
        *   
        *   @param name     The name of the wrapped terrainGen the user requests
        *   @exposed        Exposed through python API
        */
        PyTerrainGen* getTerrainGenByName( const std::string& name );

        /**
        *   Gets the PySensor wrapper of a sensor with a given name
        *   
        *   @param name     The name of the wrapped sensor the user requests
        *   @exposed        Exposed through python API
        */
        PySensor* getSensorByName( const std::string& name );

        /**
        *   Gets a list of all single-bodies belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::vector< PySingleBody* > getSingleBodies();

        /**
        *   Gets a list of all compound-bodies belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::vector< PyCompound* > getCompounds();

        /**
        *   Gets a list of all agents belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::vector< PyCoreAgent* > getAgents();

        /**
        *   Gets a list of all terrainGens belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::vector< PyTerrainGen* > getTerrainGens();

        /**
        *   Gets a list of all sensors belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::vector< PySensor* > getSensors();

        /**
        *   Gets a dictionary of all single-bodies belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::map< std::string, PySingleBody* > getSingleBodiesMap();

        /**
        *   Gets a dictionary of all compound-bodies belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::map< std::string, PyCompound* > getCompoundsMap();

        /**
        *   Gets a dictionary of all agents belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::map< std::string, PyCoreAgent* > getAgentsMap();

        /**
        *   Gets a dictionary of all terrainGens belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::map< std::string, PyTerrainGen* > getTerrainGensMap();

        /**
        *   Gets a dictionary of all sensors belonging to this scenario wrapper
        *
        *   @exposed    Exposed through python API
        *   @todo: check return policy (should not have taken ownership)
        */
        std::map< std::string, PySensor* > getSensorsMap();

        /**
        *   Gets the wrapped scenario object (used internally by runtime to ...
        *   grab the wrapped scenario object)
        *
        *   @notexposed     Not exposed through python API
        */
        tysoc::TScenario* ptr();
    };

}

//@CHECK: does the func. getAgents return a vec. with pure disowned references?
//@CHECK: does the func. getAgentsMap return a dict. with pure disowned references?

#define PYTYSOC_SCENARIO_BINDINGS(m) \
    py::class_<pytysoc::PyScenario>( m, "PyScenario" ) \
        .def( py::init<>() ) \
        .def( "addSingleBody", &pytysoc::PyScenario::addSingleBody ) \
        .def( "getSingleBodyByName", &pytysoc::PyScenario::getSingleBodyByName ) \
        .def( "getSingleBodies", &pytysoc::PyScenario::getSingleBodies ) \
        .def( "getSingleBodiesMap", &pytysoc::PyScenario::getSingleBodiesMap ) \
        .def( "addCompound", &pytysoc::PyScenario::addCompound ) \
        .def( "getCompoundByName", &pytysoc::PyScenario::getCompoundByName ) \
        .def( "getCompounds", &pytysoc::PyScenario::getCompounds ) \
        .def( "getCompoundsMap", &pytysoc::PyScenario::getCompoundsMap ) \
        .def( "addAgent", &pytysoc::PyScenario::addAgent ) \
        .def( "getAgentByName", &pytysoc::PyScenario::getAgentByName ) \
        .def( "getAgents", &pytysoc::PyScenario::getAgents ) \
        .def( "getAgentsMap", &pytysoc::PyScenario::getAgentsMap ) \
        .def( "addSensor", &pytysoc::PyScenario::addSensor ) \
        .def( "getSensorByName", &pytysoc::PyScenario::getSensorByName ) \
        .def( "getSensors", &pytysoc::PyScenario::getSensors ) \
        .def( "getSensorsMap", &pytysoc::PyScenario::getSensorsMap ) \
        .def( "addTerrainGen", &pytysoc::PyScenario::addTerrainGen ) \
        .def( "getTerrainGenByName", &pytysoc::PyScenario::getTerrainGenByName ) \
        .def( "getTerrainGens", &pytysoc::PyScenario::getTerrainGens ) \
        .def( "getTerrainGensMap", &pytysoc::PyScenario::getTerrainGensMap );