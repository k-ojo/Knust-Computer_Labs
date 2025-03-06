# Use Node.js as base image
FROM node:18

# Set working directory
WORKDIR /app

# Copy package.json and package-lock.json
COPY package*.json ./

# Install dependencies (including express)
RUN npm install

# Ensure express is installed (optional)
RUN npm install express

# Copy the rest of the backend source code
COPY . .

# Set correct permissions (optional)
RUN chmod -R 777 /app

# Expose necessary ports
EXPOSE 5000

# Compile contracts at runtime instead of during build
CMD rm -rf cache artifacts && npx hardhat compile && npm start
