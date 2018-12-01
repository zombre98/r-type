function sin(x)
   x = x / 500
   return ((3 * (x - 2)) ^ 2 + 4) * 100
end

function update(delta)
   clock = clock + delta
   local seconds = clock / 1000000
   if (seconds < 1 / 60) then return end
   clock = 0
   if (#entities == 0) then return end
   for i = 1, #entities do
      e = entities[i]
      if (e:getComponentEnemyType().type == EnemyEnum.SINUS) then
         pos = e:getComponentPosition()
         local new_pos = Position:new(pos.x - 4, sin(pos.x - 4))
         e:getComponentVelocity().x = new_pos.x - pos.x
         e:getComponentVelocity().y = new_pos.y - pos.y
      end
   end
end
