x_map = {
   [ShotEnum.ALLY] = 7,
   [ShotEnum.ENEMY] = -7,
   [ShotEnum.SHIPENEMY] = 0,
   [ShotEnum.SINUSENEMY] = -10,
}

y_map = {
   [ShotEnum.ALLY] = 0,
   [ShotEnum.ENEMY] = 0,
   [ShotEnum.SHIPENEMY] = 3,
   [ShotEnum.SINUSENEMY] = 0,
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

      velocity.x = x_map[shot]
      velocity.y = y_map[shot]
   end
end
