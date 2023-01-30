# Postprocess MCNPX-PoliMi Output to Get the Cones for Back-projection
1. Run `MPPost` to process the collision file to get the pulses.
2. Sort pulses by history number.
3. Find the position of interaction recorded in the collision file.
4. Sort the pulses by time.
5. Find the coincidecnes and generate the cones.