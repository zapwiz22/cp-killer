import * as vscode from "vscode";

export function activate(context: vscode.ExtensionContext) {
  console.log("CP Killer activated");

  const run = vscode.commands.registerCommand("zapwiz22-cp-killer.run", () => {
    const terminal = vscode.window.createTerminal({
      name: "CP Killer",
      cwd: vscode.workspace.workspaceFolders?.[0].uri.fsPath,
    });

    terminal.show();

    terminal.sendText("./judge");
  });

  context.subscriptions.push(run);
}

export function deactivate() {}
