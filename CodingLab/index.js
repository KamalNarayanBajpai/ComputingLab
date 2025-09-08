document.addEventListener('DOMContentLoaded', () => {
  const input = document.getElementById('input');
  const output = document.getElementById('output');
  const status = document.getElementById('status');
  const clearBtn = document.getElementById('clearBtn');
  const copyBtn = document.getElementById('copyBtn');
  const suggestionButtons = document.querySelectorAll('.suggestions button');

  function renderMath() {
    const latex = input.value.trim();
    if (latex) {
      output.innerHTML = `\\[${latex}\\]`;
      MathJax.typesetPromise([output]).catch(() => {
        output.innerHTML = '<span style="color: #ff5555;">Error rendering LaTeX. Check syntax.</span>';
      });
    } else {
      output.innerHTML = '';
    }
  }

  function insertLatex(latexSnippet) {
    const start = input.selectionStart;
    const end = input.selectionEnd;
    const text = input.value;

    input.value = text.substring(0, start) + latexSnippet + text.substring(end);

    // Place cursor inside first {} if present, else at end
    const cursorPos = latexSnippet.indexOf('{}');
    if (cursorPos !== -1) {
      const newPos = start + cursorPos + 1;
      input.focus();
      input.setSelectionRange(newPos, newPos);
    } else {
      const newPos = start + latexSnippet.length;
      input.focus();
      input.setSelectionRange(newPos, newPos);
    }

    renderMath();
  }

  function clearInput() {
    input.value = '';
    renderMath();
    input.focus();
  }

  function copyLatex() {
    if (!input.value.trim()) {
      showStatus('Nothing to copy.', 'error');
      return;
    }
    navigator.clipboard.writeText(input.value).then(() => {
      showStatus('LaTeX copied to clipboard!', 'success');
    }).catch(() => {
      // fallback copy method
      input.select();
      document.execCommand('copy');
      showStatus('LaTeX copied to clipboard!', 'success');
    });
  }

  function showStatus(message, type) {
    status.textContent = message;
    status.style.color = (type === 'success') ? '#03dac5' : '#ff5555';
    status.classList.add('show');
    setTimeout(() => {
      status.classList.remove('show');
    }, 2500);
  }

  // Event Listeners
  input.addEventListener('input', renderMath);

  input.addEventListener('keydown', (e) => {
    if (e.ctrlKey && e.key === 'Enter') {
      renderMath();
    }
  });

  clearBtn.addEventListener('click', clearInput);
  copyBtn.addEventListener('click', copyLatex);

  suggestionButtons.forEach(button => {
    button.addEventListener('click', () => {
      insertLatex(button.dataset.latex);
    });
  });

  // Initial render
  renderMath();
});
