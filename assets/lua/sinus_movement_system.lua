function sin(x)
   x = x / 500
   y = ((3 * (x - 2)) ^ 2 + 4) * 50
   return (y)
end

function revert_sin(x)
   return (sin(x) * -1 + 1080)
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
         -- if (i % 2 == 0) then
         --    new_pos.y = revert_sin(pos.x - 4)
         -- end
         e:getComponentVelocity().x = new_pos.x - pos.x
         e:getComponentVelocity().y = new_pos.y - pos.y
      end
   end
end
