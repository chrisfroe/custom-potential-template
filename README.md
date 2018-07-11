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

I think, there has to be a generated binding for the base class `readdy::model::potentials::PotentialOrder1` which is not in the readdybinding, see
  - http://pybind11.readthedocs.io/en/stable/advanced/misc.html#partitioning-code-over-multiple-extension-modules
  - http://pybind11.readthedocs.io/en/stable/classes.html#inheritance-and-automatic-upcasting

Defining a binding for the base class (even in the extension) fixes this.
