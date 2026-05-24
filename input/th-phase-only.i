[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 120.
  xmin = 0.0
  xmax = 2.0
[]

[Variables]
  [temp]
  []
[]

[ICs]
  [temp]
    type = FunctionIC
    variable = temp 
    function = 'if (x<=0,4.,4.)'
  []
[]

[BCs]
  [spit_heat]
    type = DirichletBC
    variable = temp
    boundary = left
    value = -6.
  []
[]

[Kernels]
#  [diffusion]
#   type = PrimaryDiffusion
#   variable = temp
#  []
  [diffusion]
   type = Diffusion_NP
   variable = temp

   lambda_unfrozen = 2.41
   lambda_frozen = 3.46
   T0 =  0.0
   Tf = -4.0

  []
#  [convection]
#    type = ExampleConvection
#    velocity = '1.0 0.0 0.0'
#    variable = temp 
#  []
#  [time_derivative]
#    type = HeatConductionTimeDerivative
#    variable = temp
#    specific_heat = 690030.
#     density_name = 1.
#  []
   [dT_dt]
     type = TempDerivative_NP
     variable = temp
     volume_heat_capacity = 690030.
     water_density = 1000.
     ice_density = 920.
     porosity = 0.336
     latent_heat_fusion = 334560.
     scale = 1.
   []
[]

#[Materials]
#  [model_inputs]
#   type = GenericConstantMaterial
#   prop_names = 'diffusivity conductivity porosity density'
#   prop_values = '0.1 1. 1. 0.'
#  []
#[]

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
  dt = 0.01
  end_time = 2.
[]

[VectorPostprocessors]
  [T]
    type = LineValueSampler
    start_point = '0 0 0'
    end_point = '2 0 0'
    num_points = 51
    sort_by = x
    variable = temp
  []
[]

[Outputs]
  file_base = out
  [csv]
    type = CSV
    sync_times = '0.1 0.2 0.5 1. 2.'
    sync_only = true
  []
[]
