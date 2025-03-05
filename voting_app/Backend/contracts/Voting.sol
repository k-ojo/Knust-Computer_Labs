// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

contract Voting {
    struct Candidate {
        string name;
        uint256 votes;
    }

    mapping(uint256 => Candidate) public candidates;
    mapping(address => bool) public hasVoted;
    uint256 public candidateCount;
    address public admin;

    event VoteCast(address indexed voter, uint256 candidateId);

    constructor() {
        admin = msg.sender;
    }

    function addCandidate(string memory _name) public {
        require(msg.sender == admin, "Only admin can add candidates.");
        candidates[candidateCount] = Candidate(_name, 0);
        candidateCount++;
    }

    function vote(uint256 _candidateId) public {
        require(!hasVoted[msg.sender], "You have already voted.");
        require(_candidateId < candidateCount, "Invalid candidate.");

        candidates[_candidateId].votes++;
        hasVoted[msg.sender] = true;

        emit VoteCast(msg.sender, _candidateId);
    }

    function getResults(uint256 _candidateId) public view returns (string memory, uint256) {
        Candidate memory candidate = candidates[_candidateId];
        return (candidate.name, candidate.votes);
    }
}
