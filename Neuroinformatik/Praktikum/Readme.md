# Praktikum Neuroinformatik

## (2b) Delte Regel

### externe Links
-  [Delta Regel](https://www.tu-ilmenau.de/universitaet/fakultaeten/fakultaet-informatik-und-automatisierung/profil/institute-und-fachgebiete/institut-fuer-technische-informatik-und-ingenieurinformatik/fachgebiet-neuroinformatik-und-kognitive-robotik/lehre/lehrveranstaltungen/delta-regel-1)
-  [Bedienungsanleitung](https://www.tu-ilmenau.de/universitaet/fakultaeten/fakultaet-informatik-und-automatisierung/profil/institute-und-fachgebiete/institut-fuer-technische-informatik-und-ingenieurinformatik/fachgebiet-neuroinformatik-und-kognitive-robotik/lehre/lehrveranstaltungen/delta-regel-1-1)
-  [Aufgabenstellung](https://www.tu-ilmenau.de/universitaet/fakultaeten/fakultaet-informatik-und-automatisierung/profil/institute-und-fachgebiete/institut-fuer-technische-informatik-und-ingenieurinformatik/fachgebiet-neuroinformatik-und-kognitive-robotik/lehre/lehrveranstaltungen/delta-regel-1-1-1)

### Installation
#### Vorraussetzungen
- Für Windows: 
```PowerShell
winget install -e --id Python.Python.3 -v 3.8.150.0
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python get-pip.py
pip install -U pip
```
- Für Linux: 
```bash
sudo pacman -Syu
sudo pacman -S python38
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python get-pip.py
pip install -U pip
```
#### pip und Python
- Installieren des Packages:
 ```shell
 pip install tui-ni-practical-course --upgrade --extra-index-url https://2022ss:5-oQR6_193gHyy1yceHh@nikrgl.informatik.tu-ilmenau.de/api/v4/projects/1730/packages/pypi/simple
 ```
- Nachinstallation von Packages
    - [PyQt5](https://pypi.org/project/PyQt5/): ``pip install PyQt5`` (5.15.7)
    - [matplotlib](https://pypi.org/project/matplotlib/): ``pip install matplotlib``(3.5.2)
    - [cryptography](https://pypi.org/project/cryptography/): ``pip install cryptography`` (37.0.2)

- Starten des Packages:
 ```shell
tui-ni-delta-rule
 ```

### Interface
![](/Neuroinformatik/Praktikum/2b_Delta-Regel/praktikum.png)

#### Lösung
##### Sigmoid 
###### Output Function
[Source Code](/Neuroinformatik/Praktikum/2b_Delta-Regel/sigmoid_output.py)
```python
import numpy
y = 1 / (1+ numpy.exp(-c*z))
```
###### Output Function Derivate
[Source Code](/Neuroinformatik/Praktikum/2b_Delta-Regel/output_function_derivate.py)
```python
dy_dz = c*y*(1-y)
```