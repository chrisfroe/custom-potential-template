Be in an environment `(test)` with readdy installed and build
```bash
(test) $ python setup.py develop
```

Test it
```bash
python run.py
```

I'm currently getting a
```python
import mypot
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ImportError: generic_type: type "MyExternalPotential" referenced unknown base type "readdy::model::potentials::PotentialOrder1"
```

