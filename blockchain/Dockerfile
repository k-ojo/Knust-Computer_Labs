# Use official Node.js image as base
FROM node:18

# Set the working directory inside the container
WORKDIR /app

# Copy package.json and package-lock.json to install dependencies first
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the entire application code to the container
COPY . .

# Expose the default React development port
EXPOSE 3000

# Command to start the development server
# Install Hardhat globally
RUN npm install -g hardhat

# Default command
CMD ["npm", "run", "dev", "start"]
