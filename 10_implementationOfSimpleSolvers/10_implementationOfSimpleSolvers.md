# Implementation of Simple Solvers – Summary

This document summarizes the key concepts and implementations described in the "Implementation of Simple Solvers" slides for OpenFOAM beginners.

---

## 🎯 Objectives

- Understand OpenFOAM solver structure and directory organization.
- Learn to build and compile custom solvers with `wmake`.
- Implement steady-state heat conduction and convection-diffusion solvers.
- Add source terms and read transport properties.
- Understand linear system convergence conditions.

---

## 🧊 Part 1: Steady-State Heat Conduction Solver

### Governing Equation:

```
∇ · (k ∇T) = 0
```

### Steps:

1. Create a new application:

   ```bash
   foamNewApp myThermalConductionSolver
   cd myThermalConductionSolver
   wmake
   ```

2. Add to `myThermalConductionSolver.C`:

   ```cpp
   #include "createTime.H"
   #include "createMesh.H"
   #include "createFields.H"
   
   solve(fvm::laplacian(k, T));
   runTime++;
   runTime.write();
   ```

3. Define fields in `createFields.H`:

   - Read field `T`
   - Read `k` from `constant/transportProperties`

4. Use modified `cavity` case for testing.

---

## 🔥 Part 2: Adding Source Terms

### Equation with Source:

```
∇ · (k ∇T) + S(x) = 0, where S(x) = Su + Sp·T
```

### Implementation:

- Add to `createFields.H`:

  ```cpp
  dimensionedScalar su("su", dimTemperature/dimTime, transportProperties);
  dimensionedScalar sp("sp", pow(dimTime,-1), transportProperties);
  ```

- Modify solver:

  ```cpp
  solve(fvm::laplacian(k, T) + su + fvm::Sp(sp, T));
  ```

- Add in `transportProperties`:

  ```foam
  su 0.02;
  sp 0.03;
  ```

---

## 🌬️ Part 3: Steady-State Convection–Diffusion Solver

### Governing Equation:

```
∇ · (U T) = ∇ · (k ∇T)
```

### Steps:

1. Copy existing solver and rename.

2. Modify main:

   ```cpp
   fvScalarMatrix TEqn(fvm::div(phi, T) - fvm::laplacian(k, T));
   TEqn.solve();
   runTime++;
   runTime.write();
   ```

3. Add velocity field `U` and compute `phi`.

---

## 🧠 Part 4: Linear System Convergence

- Convergence condition:

 ∑|a_nb| / |a_p| ≤ 1 for all cells and <1 for some

- Matrix should be diagonally dominant.
- Remedies:
  - Refine mesh
  - Use upwind scheme instead of linear

---

## ⏱️ Part 5: Adding Time Derivative

- Transient heat equation:

  ```
  ∂T/∂t - ∇ · (k ∇T) = 0
  ```

- Implement using loop structure:

  ```cpp
  while (simple.loop())
  {
      while (simple.correctNonOrthogonal())
      {
          solve(fvm::ddt(T) - fvm::laplacian(DT, T));
      }
  }
  ```

---

## 🔧 Additional Tips

- Source terms can also be implemented using `fvOptions`.
- Use `printOutfvMatrixCoeffs.H` to inspect coefficients.
- Visualize temperature fields with `paraFoam`.

---

Feel free to modify or extend this summary as you implement your own solvers.