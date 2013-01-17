using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RVO3D;
using Microsoft.Xna.Framework;

namespace RVO3DSimulatorWrapper
{
    class Class1
    {
            static void Main(string[] args)
            {
                /* Create a new simulator instance. */
                RVOSimulator sim = new RVOSimulator();


                /* Set up the scenario. */
                setupScenario(sim);                

                /* Perform (and manipulate) the simulation. */
                do
                {
                    updateVisualization(sim);
                    setPreferredVelocities(sim);
                    sim.doStep();
                }
                while (!reachedGoal(sim));                
            }


                /* Store the goals of the agents. */
            static  List<Vector3> goals = new List<Vector3>();

        static void setupScenario(RVOSimulator sim)
        {
	        /* Specify the global time step of the simulation. */
	        sim.setTimeStep(0.125f);

	        /* Specify the default parameters for agents that are subsequently added. */
	        sim.setAgentDefaults(15.0f, 10, 10.0f, 1.5f, 2.0f,new Vector3());

	        /* Add agents, specifying their start position, and store their goals on the opposite side of the environment. */
	        for (float a = 0; a < Math.PI; a += 0.1f) {
		        float z = 100.0f * (float)Math.Cos(a);
		        float r = 100.0f * (float)Math.Sin(a);

		        for (int i = 0; i < r / 2.5f; ++i) {
			        float x = r * (float)Math.Cos(i * 2.0f * (float)Math.PI / (r / 2.5f));
			        float y = r * (float)Math.Sin(i * 2.0f * (float)Math.PI / (r / 2.5f));

			        sim.addAgent(new Vector3(x, y, z));
			        goals.Add(sim.getAgentPosition(sim.getNumAgents() - 1));
		        }
	        }
        }

        static  void updateVisualization(RVOSimulator sim)
        {	
	        /* Output the position for all the agents. */
	        for (int i = 0; i < sim.getNumAgents(); ++i) {
		        Console.WriteLine(sim.getAgentPosition(i));;
	        }
        }

        static void setPreferredVelocities(RVOSimulator sim)
        {
	        for (int i = 0; i < sim.getNumAgents(); ++i) {
		        Vector3 goalVector = goals[i] - sim.getAgentPosition(i);

		        if ((goalVector.LengthSquared()) > 1.0f) {
			        goalVector = Vector3.Normalize(goalVector);
		        }

		        sim.setAgentPrefVelocity(i, goalVector);
	        }
        }

        static  bool reachedGoal(RVOSimulator sim)
        {
	        /* Check if all agents have reached their goals. */
	        for (int i = 0; i < sim.getNumAgents(); ++i) {
		        if ((sim.getAgentPosition(i) - goals[i]).LengthSquared() > 4.0f * sim.getAgentRadius(i) * sim.getAgentRadius(i)) {
			        return false;
		        }
	        }

	        return true;
        }


            }
}
