file(
  COPY
    getkw.py
    pyparsing.py
  DESTINATION
    ${INSTALL_PYMODDIR}
  )

install(
  FILES
    getkw.py
    pyparsing.py
  DESTINATION
    ${INSTALL_PYMODDIR}
  COMPONENT
    bin
  )
