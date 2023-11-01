from main_window import MainWindow
from PySide6.QtWidgets import QApplication
from PySide6.QtGui import QScreen

app = QApplication([])
window = MainWindow()

window.setGeometry(0, 0, 800, 600)
screen_geometry = QScreen.availableGeometry(QApplication.primaryScreen())
screenX = (screen_geometry.width() - window.width()) / 2
screenY = (screen_geometry.height() - window.height()) / 2
window.move(screenY, screenY)
window.show()


app.exec()