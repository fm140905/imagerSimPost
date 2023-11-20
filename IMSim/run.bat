@echo off
set sim_dir=C:\Users\ming\Documents\imagerSimPost\IMSim
set exe_dir=C:\Users\ming\Documents\imagerSimPost\build\Sources
set collision_file_name=comptonImager0.d

cd /d %sim_dir%

echo "  sort by hist"
"%exe_dir%\sortbyhist\Release\sortbyhist" %sim_dir%

echo "  find pos"
"%exe_dir%\findposition\Release\findposition" %sim_dir% %collision_file_name%

echo "  sort by time"
"%exe_dir%\sortbytime\Release\sortbytime" %sim_dir%

echo "  find coincidences"
"%exe_dir%\findCoincidences\Release\findCoincidences" %sim_dir%

echo "Done."