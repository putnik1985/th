[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 80.
  xmin = 0.0
  xmax = 5.0
[]

[Variables]
  [T]
  []
[]

[ICs]
  [TIC]
    type = FunctionIC
    variable = T 
    function = '267.'
  []
[]

[BCs]
  [left_temp]
    type = DirichletBC
    variable = T
    boundary = left
    value = 267.
  []

  [right_temp]
    type = DirichletBC
    variable = T
    boundary = right
    value = 273.
  []
[]

[Kernels]

  [diffusion]
   type = Diffusion_NP
   variable = T

   kice = 3.2
   thermal_inertia = 250.
   porosity = 0.4
   volumetric_filling = 0.8

   density = 2000.
   capacity = 800.
  []

   [dT_dt]
     type = TempDerivative_NP
     variable = T

     density = 2000.
     capacity = 800.
   []
[]

[Preconditioning]
  [andy]
    type = SMP
    full = true
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it'
    petsc_options_value = 'gmres bjacobi 1E-15 1E-10 10000'
  []
[]

[Executioner]
  type = Transient
  solve_type = PJFNK
  dt = 0.02
  end_time = 1.0
[]

[VectorPostprocessors]
  [T]
    type = LineValueSampler
    start_point = '0 0 0'
    end_point = '5 0 0'
    num_points = 80
    sort_by = x
    variable = T
  []
[]

[Outputs]
  file_base = out
  [csv]
    type = CSV
  []
[]
