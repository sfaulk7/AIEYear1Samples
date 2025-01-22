/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"

//destroyerTexture = LoadTexture("res/9.png");
//critterTexture = LoadTexture("res/10.png");

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    

    int screenWidth = 800;
    int screenHeight = 450;

    int currentFPS = 0;
    int previousFPS = 0;
    bool averageCalculated = false;
    int averageCount = 0;
    int averageCalculation = 0;
    int averageFPS = 0;
    int lostFPS = 0;
    Color colorFPS = Color(BLANK);

    int crittersInPool = 0;

    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));


    Critter critters[1000]; 

    // create some critters
    const int CRITTER_COUNT = 50;
    const int MAX_VELOCITY = 80;

    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        // create a random direction vector for the velocity
        Vector2 velocity = { -100+(rand()%200), -100+(rand()%200) };
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);

        // create a critter in a random location
        critters[i].Init(
            { (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) },
            velocity,
            12, "res/10.png");
    }


    Critter destroyer;
    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, "res/9.png");

    float timer = 1;
    Vector2 nextSpawnPos = destroyer.GetPosition();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        //Draw bounds
        //int screenLeft = screenWidth * .45;
        //int screenRight = screenWidth * .55;
        //int screenTop = screenHeight * .45;
        //int screenBottom = screenHeight * .55;
        int screenLeft = screenWidth * .05;
        int screenRight = screenWidth * .95;
        int screenTop = screenHeight * .05;
        int screenBottom = screenHeight * .95;

        //Draw Top left to Top right line
        DrawLine(screenLeft, screenTop, screenRight, screenTop, Color(RED));
        //Draw Top left to bottom left line
        DrawLine(screenLeft, screenTop, screenLeft, screenBottom, Color(RED));
        //Draw bottom left to bottom right line
        DrawLine(screenLeft, screenBottom, screenRight, screenBottom, Color(RED));
        //Draw Top right to bottom right line
        DrawLine(screenRight, screenTop, screenRight, screenBottom, Color(RED));

        float delta = GetFrameTime();

        // update the destroyer
        destroyer.Update(delta);
        // check destroyer against screen bounds
        //Checks for left of screen
        if (destroyer.GetX() - destroyer.GetRadius() < screenLeft)
        {
            destroyer.SetX(screenLeft + destroyer.GetRadius());
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        //Checks for right of screen
        if (destroyer.GetX() + destroyer.GetRadius() > screenRight)
        {
            destroyer.SetX(screenRight - destroyer.GetRadius());
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        //Checks for top of screen
        if (destroyer.GetY() - destroyer.GetRadius() < screenTop)
        {
            destroyer.SetY(screenTop + destroyer.GetRadius());
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }
        //Checks for bottom of screen
        if (destroyer.GetY() + destroyer.GetRadius() > screenBottom)
        {
            destroyer.SetY(screenBottom - destroyer.GetRadius());
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }

        // update the critters
        // (dirty flags will be cleared during update)
        for (int i = 0; i < CRITTER_COUNT; i++)
        {
            critters[i].Update(delta);

            // check each critter against screen bounds
            //Checks for left of screen
            if (critters[i].GetX() - critters[i].GetRadius() < screenLeft) 
            {
                critters[i].SetX(screenLeft + critters[i].GetRadius());
                critters[i].SetVelocity(Vector2{ -critters[i].GetVelocity().x, critters[i].GetVelocity().y });
            }
            //Checks for right of screen
            if (critters[i].GetX() + critters[i].GetRadius() > screenRight)
            {
                critters[i].SetX(screenRight - critters[i].GetRadius());
                critters[i].SetVelocity(Vector2{ -critters[i].GetVelocity().x, critters[i].GetVelocity().y });
            }
            //Checks for top of screen
            if (critters[i].GetY() - critters[i].GetRadius() < screenTop)
            {
                critters[i].SetY(screenTop + critters[i].GetRadius());
                critters[i].SetVelocity(Vector2{ critters[i].GetVelocity().x, -critters[i].GetVelocity().y });
            }
            //Checks for bottom of screen
            if (critters[i].GetY() + critters[i].GetRadius() > screenBottom)
            {
                critters[i].SetY(screenBottom - critters[i].GetRadius());
                critters[i].SetVelocity(Vector2{ critters[i].GetVelocity().x, -critters[i].GetVelocity().y });
            }

            // kill any critter touching the destroyer
            // simple circle-to-circle collision check
            float dist = Vector2Distance(critters[i].GetPosition(), destroyer.GetPosition());
            if (dist < critters[i].GetRadius() + destroyer.GetRadius())
            {
                //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                // this would be the perfect time to put the critter into an object pool
                //critters[i].Destroy();
                //Put it in an object pool
                critters[i].ToPool();
                crittersInPool++;
            }
        }
                
        // check for critter-on-critter collisions
        for (int i = 0; i < CRITTER_COUNT; i++)
        {            
            for (int j = 0; j < CRITTER_COUNT; j++){
                if (i == j || critters[i].IsDirty()) // note: the other critter (j) could be dirty - that's OK
                    continue;
                // check every critter against every other critter
                float dist = Vector2Distance(critters[i].GetPosition(), critters[j].GetPosition());
                if (dist < critters[i].GetRadius() + critters[j].GetRadius())
                {
                    // collision!
                    // do math to get critters bouncing
                    Vector2 normal = Vector2Normalize( Vector2Subtract(critters[j].GetPosition(), critters[i].GetPosition()));

                    // not even close to real physics, but fine for our needs
                    critters[i].SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
                    // set the critter to *dirty* so we know not to process any more collisions on it
                    critters[i].SetDirty(); 

                    // we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
                    // to make sure the other critter is clean before we do the collision response
                    if (!critters[j].IsDirty()) {
                        critters[j].SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                        critters[j].SetDirty();
                    }
                    break;
                }
            }
        }

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1;

            // find any dead critters and spit them out (respawn)
            for (int i = 0; i < CRITTER_COUNT; i++)
            {
                if (critters[i].InPool())
                {
                    Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

                    // get a position behind the destroyer, and far enough away that the critter won't bump into it again
                    Vector2 pos = destroyer.GetPosition();
                    pos = Vector2Add(pos, Vector2Scale(normal, -50));
                    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    // its pretty ineficient to keep reloading textures. ...if only there was something else we could do
                    //critters[i].Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, "res/10.png");
                    //Converted to an object pool
                    critters[i].OutPool();
                    crittersInPool--;
                    critters[i].SetPosition(pos);

                    break;
                }
            }
            nextSpawnPos = destroyer.GetPosition();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw the critters
        for (int i = 0; i < CRITTER_COUNT; i++)
        {
            critters[i].Draw();
        }
        // draw the destroyer
        // (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
        // destroyer, it's because the origin is at the top-left. ...you could fix that!)
            //Fixed that in Critter.cpp
        destroyer.Draw();

        //Displays fps
        //The fps is green if it stays the same or increases and turns red if it decreases
        currentFPS = GetFPS();
        if (currentFPS >= previousFPS)
        {
            colorFPS = Color(GREEN);
        }
        else
        {
            colorFPS = Color(RED);
            lostFPS = currentFPS - previousFPS;
        }
        if (averageCalculated == false)
        {
            averageCount++;
            averageCalculation = averageCalculation + currentFPS;

            //Change this to change the amount that you average by
            if (averageCount == 1000)
            {
                averageCalculated = true;
            }
        }
        if (averageCalculated == true)
        {
            averageCalculated = false;
            averageFPS = averageCalculation / (averageCount);
            averageCount = 0;
            averageCalculation = 0;
        }

        previousFPS = currentFPS;
        DrawText(FormatText("Average FPS: %d", averageFPS), GetScreenWidth() * .15, GetScreenHeight() * .95, 20, Color(BLACK));
        DrawText(FormatText("FPS: %d", currentFPS), GetScreenWidth() * .45, GetScreenHeight() * .95, 20, colorFPS);
        DrawText(FormatText("FPS losses: %d", lostFPS), GetScreenWidth() * .65, GetScreenHeight() * .95, 20, Color(RED));

        //Displays critters in pool
        DrawText(FormatText("Critters in pool: %d", crittersInPool), GetScreenWidth() * .05, GetScreenHeight() * .01, 20, Color(RED));

        //Before Optimizations:
        //FPS usually averages around 2400FPS to 2800FPS and has drops all the way down to 1800FPS

        //After Optimizations:
        //FPS usually averages around 

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        critters[i].Destroy();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}