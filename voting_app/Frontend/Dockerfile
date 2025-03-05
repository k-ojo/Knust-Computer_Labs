# Use Node.js as base image
FROM node:18

# Set working directory
WORKDIR /app

# Copy package.json and package-lock.json
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the rest of the frontend source code
COPY . .

# Build the React app
RUN npm run build

# Expose necessary port
EXPOSE 3000

# Start the frontend
CMD ["npm", "start"]