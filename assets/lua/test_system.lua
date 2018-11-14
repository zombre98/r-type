function update(delta)
   print("===LUA===")
   print("setting comp velocity to 5.6")
   entities[1]:getComponentVelocity().x = 5.6
   print("creating new pos component")
   entities[1]:addComponentPosition(666.0, 45.0)
   print("getting new pos Component x:", entities[1]:getComponentPosition().x)
   print("===LUA END===")
end
