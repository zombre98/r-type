function update(delta)
   clock = clock + delta
   local seconds = clock / 1000000
   if (seconds < 1 / 30) then return end
   clock = 0
   if (#entities == 0) then return end

   for i = 1, #entities do
      local e = entities[i]
      local enemy = e:getComponentEnemyType().type
      local velocity = e:getComponentVelocity()

      if (enemy == EnemyEnum.CLASSIC) then
         velocity.x = -7
      elseif (enemy == EnemyEnum.SHIP) then
         pos = e:getComponentPosition();
         local new_pos = Position:new(pos.x - 3, ((pos.x - 3) / 2))
         velocity.x = new_pos.x - pos.x
         velocity.y = new_pos.y - pos.y
      end
   end
end
