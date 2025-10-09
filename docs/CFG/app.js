// Minimal AST builder for shell-like input
function parseCommand(input) {
  input = input.trim();

  // Handle parentheses (subshell)
  const parenMatch = input.match(/\(([^()]*)\)/);
  if (parenMatch) {
    return {
      type: "SUBSHELL",
      children: [parseCommand(parenMatch[1])]
    };
  }

  // Handle logical AND/OR
  if (input.includes("&&")) {
    const [left, right] = input.split("&&", 2);
    return { type: "AND", children: [parseCommand(left), parseCommand(right)] };
  }

  if (input.includes("||")) {
    const [left, right] = input.split("||", 2);
    return { type: "OR", children: [parseCommand(left), parseCommand(right)] };
  }

  // Handle pipe
  if (input.includes("|")) {
    const [left, right] = input.split("|", 2);
    return { type: "PIPE", children: [parseCommand(left), parseCommand(right)] };
  }

  // Handle redirection
  const redirMatch = input.match(/(.*?)(<|>|>>|<<)\s*(\S+)/);
  if (redirMatch) {
    return {
      type: "COMMAND",
      value: redirMatch[1].trim(),
      children: [{ type: "REDIR", value: `${redirMatch[2]} ${redirMatch[3]}` }]
    };
  }

  // Default simple command
  return { type: "COMMAND", value: input };
}

// Draw AST tree with D3.js
function drawTree(ast) {
  const svg = d3.select("#tree");
  svg.selectAll("*").remove();

  const width = +svg.attr("width");
  const height = +svg.attr("height");

  const root = d3.hierarchy(ast);
  const tree = d3.tree().size([width - 100, height - 100]);
  const nodes = tree(root);

  // Links
  svg.selectAll("line")
    .data(nodes.links())
    .enter()
    .append("line")
    .attr("x1", d => d.source.x + 50)
    .attr("y1", d => d.source.y + 50)
    .attr("x2", d => d.target.x + 50)
    .attr("y2", d => d.target.y + 50)
    .attr("stroke", "#555");

  // Nodes
  svg.selectAll("circle")
    .data(nodes.descendants())
    .enter()
    .append("circle")
    .attr("cx", d => d.x + 50)
    .attr("cy", d => d.y + 50)
    .attr("r", 25)
    .attr("fill", "#238636");

  // Labels
  svg.selectAll("text")
    .data(nodes.descendants())
    .enter()
    .append("text")
    .attr("x", d => d.x + 50)
    .attr("y", d => d.y + 55)
    .attr("text-anchor", "middle")
    .attr("fill", "white")
    .text(d => d.data.value || d.data.type);
}

// Hook input
document.getElementById("run").addEventListener("click", () => {
  const cmd = document.getElementById("cmd").value;
  if (!cmd) return;
  const ast = parseCommand(cmd);
  drawTree(ast);
});
