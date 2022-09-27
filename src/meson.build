namaste_sources = [
  'main.c',
  'namaste-application.c',
  'namaste-window.c',
]

namaste_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1'),
  dependency('webkit2gtk-5.0'),
]

namaste_sources += gnome.compile_resources('namaste-resources',
  'namaste.gresource.xml',
  c_name: 'namaste'
)

executable('namaste', namaste_sources,
  dependencies: namaste_deps,
       install: true,
)
