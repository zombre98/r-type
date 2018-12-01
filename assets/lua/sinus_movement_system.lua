function update(delta)
   clock = clock + delta
   local seconds = clock / 1000000
   if (seconds < 1 / 60) then return end
   clock = 0
   if (#entities == 0) then return end
   for i = 1, #entities do
      e = entities[i]
      if (e:getComponentEnemyType().type == EnemyEnum.SINUS) then
         e:getComponentVelocity().x = -10
      end
   end
end
