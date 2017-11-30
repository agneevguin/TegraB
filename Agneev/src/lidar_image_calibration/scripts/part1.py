import cv2
from camera_calibration.calibrator import MonoCalibrator, ChessboardInfo

numImages = 23

images = [ cv2.imread( '../Images/Camera_indoor_checkerboard/screenshot_{:04d}.png'.format( i ) ) for i in range( numImages ) ]

board = ChessboardInfo()
board.n_cols = 8
board.n_rows = 6
board.dim = 0.041

mc = MonoCalibrator( [ board ], cv2.CALIB_FIX_K3 )
mc.cal( images )
print( mc.as_message() )

mc.do_save()
