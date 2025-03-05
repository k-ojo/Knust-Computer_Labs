const hre = require("hardhat");

async function main() {
  const Voting = await hre.ethers.deployContract("Voting"); // Use deployContract
  await Voting.waitForDeployment(); // Use waitForDeployment() instead of deployed()

  console.log(`Voting contract deployed to: ${Voting.target}`);
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
