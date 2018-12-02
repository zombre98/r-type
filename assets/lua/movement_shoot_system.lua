v_map = {
   [ShotEnum.ALLY] = 7,
   [ShotEnum.ENEMY] = -7,
   [ShotEnum.SHIPENEMY] = 5,
   [ShotEnum.SINUSENEMY] = -10,
}

function update(delta)
   clock = clock + delta
   local seconds = clock / 1000000
   if (seconds < 1 / 90) then return end
   clock = 0
   if (#entities == 0) then return end

   for i = 1, #entities do
      local e = entities[i]
      local shot = e:getComponentShotType().type
      local velocity = e:getComponentVelocity()

      velocity.x = v_map[shot]
   end
end
