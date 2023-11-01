# General notes

This project uses Python 3.11.x but keep compatibility with Python 3.9.x.

# (REQUIRED) Development environment

Assuming you have the right Python version, you can create a virtual environment with all dependencies:

Create an environment which contains the requirements of ALL microservices that we have:
```sh
rm -rf venv-up-all
python3.11 -m venv venv-up-all

source venv-up-all/bin/activate
python -m pip install --upgrade pip
pip install --force-reinstall -r requirements.txt
```

# Resources

- Creating a GUI interface: https://doc.qt.io/qtforpython-6/modules.html
- Plotting a real-time graph: https://www.pythonguis.com/tutorials/pyside6-plotting-pyqtgraph/
- Serial communication with a microcontroller: https://pyserial.readthedocs.io/en/latest/shortintro.html