import React, { useState, useEffect } from "react";
import { BrowserProvider, Contract } from "ethers";
import VotingABI from "./VotingABI.json";  // Ensure this file exists

const CONTRACT_ADDRESS = "YOUR_DEPLOYED_CONTRACT_ADDRESS"; // Replace with actual contract address

function App() {
    const [account, setAccount] = useState(null);
    const [candidates, setCandidates] = useState([]);
    const [contract, setContract] = useState(null);

    useEffect(() => {
        connectWallet();
    }, []);

    async function connectWallet() {
        if (window.ethereum) {
            const provider = new BrowserProvider(window.ethereum);
            const signer = await provider.getSigner();
            const contractInstance = new Contract(CONTRACT_ADDRESS, VotingABI, signer);
            setContract(contractInstance);

            const accounts = await window.ethereum.request({ method: "eth_requestAccounts" });
            setAccount(accounts[0]);

            const count = await contractInstance.candidateCount();
            let candidatesArray = [];
            for (let i = 0; i < count; i++) {
                const candidate = await contractInstance.getResults(i);
                candidatesArray.push({ id: i, name: candidate[0], votes: candidate[1].toString() });
            }
            setCandidates(candidatesArray);
        } else {
            alert("Please install MetaMask.");
        }
    }

    async function vote(candidateId) {
        if (!contract) return;
        try {
            const tx = await contract.vote(candidateId);
            await tx.wait();
            alert("Vote cast successfully!");
        } catch (error) {
            alert("Error: " + error.message);
        }
    }

    return (
        <div>
            <h1>Blockchain Voting App</h1>
            <button onClick={connectWallet}>Connect Wallet</button>
            <p>Connected Account: {account}</p>
            <h2>Candidates</h2>
            {candidates.map((candidate) => (
                <div key={candidate.id}>
                    <p>{candidate.name} - {candidate.votes} votes</p>
                    <button onClick={() => vote(candidate.id)}>Vote</button>
                </div>
            ))}
        </div>
    );
}
export default App;
