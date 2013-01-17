using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using RVO2D;

namespace ConsoleApplication1
{
    class Program
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
            } while (!reachedGoal(sim));

            
        }

            /* Store the goals of the agents. */
            static List<Vector2> goals= new  List<Vector2>();

            static void setupScenario(RVOSimulator sim)
            {
              /* Specify the global time step of the simulation. */
              sim.setTimeStep(0.25f);

              /* Specify the default parameters for agents that are subsequently added. */
              sim.setAgentDefaults(15.0f, 10, 5.0f, 5.0f, 2.0f, 2.0f,new Vector2());

              /*
               * Add agents, specifying their start position, and store their goals on the
               * opposite side of the environment.
               */
              for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                  sim.addAgent(new Vector2(55.0f + i * 10.0f,  55.0f + j * 10.0f));
                  goals.Add(new Vector2(-75.0f, -75.0f));
                    
                  sim.addAgent(new Vector2(-55.0f - i * 10.0f,  55.0f + j * 10.0f));
                  goals.Add(new Vector2(75.0f, -75.0f));

                  sim.addAgent(new Vector2(55.0f + i * 10.0f, -55.0f - j * 10.0f));
                  goals.Add(new Vector2(-75.0f, 75.0f));

                  sim.addAgent(new Vector2(-55.0f - i * 10.0f, -55.0f - j * 10.0f));
                  goals.Add(new Vector2(75.0f, 75.0f));
                }
              }

              /*
               * Add (polygonal) obstacles, specifying their vertices in counterclockwise
               * order.
               */
                List<Vector2> obstacle1 = new List<Vector2>();
                List<Vector2>  obstacle2= new List<Vector2>();
                List<Vector2>  obstacle3= new List<Vector2>();
                List<Vector2>  obstacle4= new List<Vector2>();

              obstacle1.Add(new Vector2(-10.0f, 40.0f));
              obstacle1.Add(new Vector2(-40.0f, 40.0f));
              obstacle1.Add(new Vector2(-40.0f, 10.0f));
              obstacle1.Add(new Vector2(-10.0f, 10.0f));

              obstacle2.Add(new Vector2(10.0f, 40.0f));
              obstacle2.Add(new Vector2(10.0f, 10.0f));
              obstacle2.Add(new Vector2(40.0f, 10.0f));
              obstacle2.Add(new Vector2(40.0f, 40.0f));

              obstacle3.Add(new Vector2(10.0f, -40.0f));
              obstacle3.Add(new Vector2(40.0f, -40.0f));
              obstacle3.Add(new Vector2(40.0f, -10.0f));
              obstacle3.Add(new Vector2(10.0f, -10.0f));

              obstacle4.Add(new Vector2(-10.0f, -40.0f));
              obstacle4.Add(new Vector2(-10.0f, -10.0f));
              obstacle4.Add(new Vector2(-40.0f, -10.0f));
              obstacle4.Add(new Vector2(-40.0f, -40.0f));

              sim.addObstacle(obstacle1);
              sim.addObstacle(obstacle2);
              sim.addObstacle(obstacle3);
              sim.addObstacle(obstacle4);

              /* Process the obstacles so that they are accounted for in the simulation. */
              sim.processObstacles();
            }


            static void updateVisualization(RVOSimulator sim)
            {              
              /* Output the current position of all the agents. */
              for (int i = 0; i < sim.getNumAgents(); ++i) {
                Console.WriteLine(sim.getAgentPosition(i) );
              }

            }

            static Random r = new Random();
            static void setPreferredVelocities(RVOSimulator sim)
            {
              /* 
               * Set the preferred velocity to be a vector of unit magnitude (speed) in the
               * direction of the goal.
               */
            #pragma omp parallel for
              for (int i = 0; i < sim.getNumAgents(); ++i) {
                Vector2 goalVector = goals[i] - sim.getAgentPosition(i);

                if ((goalVector.LengthSquared()) > 1.0f) {
                  goalVector = Vector2.Normalize(goalVector);
                }

                sim.setAgentPrefVelocity(i, goalVector);
    
                /*
                 * Perturb a little to avoid deadlocks due to perfect symmetry.
                 */

                float angle = (float)r.NextDouble() * 2.0f * (float)Math.PI ;
                float dist = (float)r.NextDouble() * 0.0001f ;
    
                sim.setAgentPrefVelocity(i, sim.getAgentPrefVelocity(i) + 
                                          dist * new Vector2((float) Math.Cos(angle), (float)Math.Sin(angle)));
              }
            }

            static bool reachedGoal(RVOSimulator sim)
            {
              /* Check if all agents have reached their goals. */
              for (int i = 0; i < sim.getNumAgents(); ++i) {
                if ((sim.getAgentPosition(i) - goals[i]).LengthSquared() > 20.0f * 20.0f) {
                  return false;
                }
              }

              return true;
            }



    }
}
