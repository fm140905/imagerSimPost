@echo off
set sim_dir=C:\Users\ming\Documents\imagerSimPost\IMSim
set exe_dir=C:\Users\ming\Documents\imagerSimPost\build
set collision_file_name=comptonImager0.d

cd /d %sim_dir%

echo "  sort by hist"
"%exe_dir%\Sources\sortbyhist\Release\sortbyhist" %sim_dir%

echo "  find pos"
"%exe_dir%\Sources\findposition\Release\findposition" %sim_dir% %collision_file_name%

echo "  sort by time"
"%exe_dir%\Sources\sortbytime\Release\sortbytime" %sim_dir%

echo "  find coincidences"
"%exe_dir%\Sources\findCoincidences\Release\findCoincidences" %sim_dir%

echo "Done."