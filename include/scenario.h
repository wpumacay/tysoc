
#pragma once

#include <terrain/terrain.h>
#include <agent/agent.h>
#include <sensor/sensor.h>

namespace tysoc
{

    enum ScenarioState
    {
        IDLE,
        RUNNING,
        FINISHED
    };

    class TScenario
    {
        protected :

        std::map< std::string, tysocagent::TAgent* > m_agents;
        std::map< std::string, tysocsensor::TSensor* > m_sensors;
        std::vector< tysocterrain::TTerrainGenerator* > m_terrainGenerators;

        ScenarioState m_state;


        public :

        TScenario();
        ~TScenario();

        ScenarioState state();

        void addAgent( tysocagent::TAgent* agent );
        void addSensor( tysocsensor::TSensor* sensor );
        void addTerrainGenerator( tysocterrain::TTerrainGenerator* terrainGenerator );

        tysocagent::TAgent* getAgent( const std::string& name );
        tysocsensor::TSensor* getSensor( const std::string& name );

        std::map< std::string, tysocagent::TAgent* > getAgents();
        std::vector< tysocterrain::TTerrainGenerator* > getTerrainGenerators();

        virtual void initialize();
        virtual void update();
    };



}