
 // ======== Tokenizer ========
 function tokenize(str) {
    const result = [];
    const regex = /int|frac|sqrt|dx|[a-zA-Z]|[0-9]+|\^|_|,|[+\-*/()]|\n/g;
    let match;
    while ((match = regex.exec(str)) !== null) {
      result.push(match[0]);
    }
    return result;
  }

  let tokens, i;

  // ======== Parser ========
  function parseExpression() {
    let node = parseFactor();
    while (tokens[i] === "+" || tokens[i] === "-") {
      let op = tokens[i++];
      let right = parseFactor();
      node = { type: op, left: node, right };
    }
    return node;
  }

  function parseFactor() {
    let node;
    let tok = tokens[i];

    if (tok === "(") {
      i++;
      node = parseExpression();
      i++; // consume ")"
    } else if (tok === "int") {
      i++;
      let lower = null, upper = null;
      if (tokens[i] === "_") {
        i++;
        lower = parseFactor();
      }
      if (tokens[i] === "^") {
        i++;
        upper = parseFactor();
      }
      let body = parseExpression();
      if (tokens[i] === "dx") i++;
      node = { type: "INT", lower, upper, body };
    } else if (tok === "frac") {
      i++; // skip 'frac'
      if (tokens[i] === "(") i++;
      let num = parseExpression();
      if (tokens[i] === ",") i++;
      let den = parseExpression();
      if (tokens[i] === ")") i++;
      node = { type: "FRAC", num, den };
    } else if (tok === "sqrt") {
      i++;
      if (tokens[i] === "(") i++;
      let inside = parseExpression();
      if (tokens[i] === ")") i++;
      node = { type: "SQRT", body: inside };
    } else if (/^[a-zA-Z]$/.test(tok) || /^[0-9]+$/.test(tok)) {
      node = { type: "ATOM", value: tok };
      i++;
    } else {
      i++;
      node = { type: "ATOM", value: tok };
    }

    // Handle superscript/subscript chains
    while (tokens[i] === "^" || tokens[i] === "_") {
      let op = tokens[i++];
      let child = parseFactor();
      node = { type: op, base: node, exp: child };
    }

    return node;
  }

  function parseLine() {
    let exprs = [];
    while (i < tokens.length) {
      exprs.push(parseExpression());
    }
    return exprs;
  }

  // ======== Code Generator ========
  function generate(node) {
    if (!node) return "";
    if (node.type === "ATOM") return node.value;
    if (node.type === "+") return generate(node.left) + " + " + generate(node.right);
    if (node.type === "-") return generate(node.left) + " - " + generate(node.right);
    if (node.type === "^") return generate(node.base) + "<sup>" + generate(node.exp) + "</sup>";
    if (node.type === "_") return generate(node.base) + "<sub>" + generate(node.exp) + "</sub>";
    if (node.type === "INT") {
      return `<span class="integral">∫` +
        (node.lower ? `<sub>${generate(node.lower)}</sub>` : "") +
        (node.upper ? `<sup>${generate(node.upper)}</sup>` : "") +
        `</span>` + generate(node.body);
    }
    if (node.type === "FRAC") {
      return `<span class="frac"><span>${generate(node.num)}</span><span class="den">${generate(node.den)}</span></span>`;
    }
    if (node.type === "SQRT") {
      return `√(${generate(node.body)})`;
    }
    return "";
  }

  // ======== Multi-line Support ========
  function parseAndRender(input) {
    const lines = input.split("\n");
    return lines.map(line => {
      if (!line.trim()) return "";
      tokens = tokenize(line);
      i = 0;
      const exprs = parseLine();
      return exprs.map(generate).join(" ");  // multiple exprs per line
    }).join("\n");
  }

  // ======== Hook to UI ========
  const editor = document.getElementById("editor");
  const preview = document.getElementById("preview");

  editor.addEventListener("input", () => {
    preview.innerHTML = parseAndRender(editor.value);
  });

