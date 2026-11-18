PY=python3
test:
	@for t in program1 program2 v11_features errors; do \
	  $(PY) brainrot_scanner.py tests/$$t.br out/$$t || true; done
