const hre = require("hardhat");
const express = require("express");

const app = express();
const PORT = 5000;

async function main() {
  const Voting = await hre.ethers.deployContract("Voting");
  await Voting.waitForDeployment();

  console.log(`Voting contract deployed to: ${Voting.target}`);

  // Expose contract address via API
  app.get("/contract", (req, res) => {
    res.json({ contractAddress: Voting.target });
  });

  app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
  });
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
