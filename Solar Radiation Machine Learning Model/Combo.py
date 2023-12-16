# Step 0: Import Libraries
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor, GradientBoostingRegressor
from sklearn.linear_model import LinearRegression, Ridge, Lasso
from sklearn.svm import SVR
from sklearn.neighbors import KNeighborsRegressor
from sklearn.neural_network import MLPRegressor
from sklearn.metrics import r2_score, mean_squared_error
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
import warnings
from sklearn.exceptions import ConvergenceWarning

# Step 1: Data Preprocessing
data = pd.read_csv('SolarPrediction.csv')  # Import data from csv

# Step 2: Data PreProcessing
# Convert UnixTime to datetime formal
data['DateTime'] = pd.to_datetime(data['UNIXTime'], unit='s')  # Convert UnixTime to decimal time format
data['TimeOfDay'] = data['DateTime'].dt.hour + data['DateTime'].dt.minute / 60.0
# Convert TimeSunRise to decimal time format
data['TimeSunRise'] = pd.to_datetime(data['TimeSunRise'], format='%H:%M:%S')
data['TimeSunRise'] = data['TimeSunRise'].dt.hour + data['TimeSunRise'].dt.minute / 60.0
# Convert TimeSunSet to decimal time format
data['TimeSunSet'] = pd.to_datetime(data['TimeSunSet'], format='%H:%M:%S')
data['TimeSunSet'] = data['TimeSunSet'].dt.hour + data['TimeSunSet'].dt.minute / 60.0
# Remove unecessary variables from dataset
data = data.drop(['UNIXTime', 'Data', 'Time', 'DateTime'], axis=1) 

# Step 3: Data Splitting
x = data.drop('Radiation', axis=1)  # All variables
y = data['Radiation']
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2)

# Step 4: Model Selection and Comparison
models = {
    'Linear Regression': LinearRegression(),
    'Ridge Regression': Ridge(),
    'Lasso Regression': Lasso(),
    'Random Forest': RandomForestRegressor(),
    'Gradient Boosting': GradientBoostingRegressor(),
    'Support Vector Machine': SVR(),
    'K-Nearest Neighbors': KNeighborsRegressor(),
    'Neural Network': MLPRegressor()
}

print('Model Comparison')
print('------------------------------------------------------------------------------------------------------------------------------')

# Step 5: Test Model and Get Metrics
results_r2 = {}
results_rmse_train = {}
results_rmse_test = {}
with warnings.catch_warnings():
  warnings.filterwarnings("ignore", category=ConvergenceWarning)
  for name, model in models.items(): # Test Model
    pipeline = make_pipeline(StandardScaler(), model)
    pipeline.fit(x_train, y_train)
    predictions_train = pipeline.predict(x_train)
    predictions_test = pipeline.predict(x_test)
    # Metrics of fit for models
    r2 = r2_score(y_test, predictions_test)
    rmse_train = mean_squared_error(y_train, predictions_train)
    rmse_test = mean_squared_error(y_test, predictions_test)
    results_r2[name] = r2
    results_rmse_train[name] = rmse_train
    results_rmse_test[name] = rmse_test
    # Print Results
    print(f'R-squared for {name}: {r2:.6f}')
    print(f'Training Mean Squared Error for {name}: {rmse_train:.6f}')
    print(f'Testing Mean Squared Error for {name}: {rmse_test:.6f}')
    print('------------------------------------------------------------------------------------------------------------------------------')

# Step 6: Compare the results
best_model_r2 = max(results_r2, key=results_r2.get)
print(f'Best model based on R-squared: {best_model_r2} with R-squared of {results_r2[best_model_r2]:.6f}')
best_model_rmse_train = min(results_rmse_train, key=results_rmse_train.get)
print(f'Best model based on Training Mean Squared Error: {best_model_rmse_train} with RMSE of {results_rmse_train[best_model_rmse_train]:.6f}')
best_model_rmse_test = min(results_rmse_test, key=results_rmse_test.get)
print(f'Best model based on Testing Mean Squared Error: {best_model_rmse_test} with RMSE of {results_rmse_test[best_model_rmse_test]:.6f}')

# Step 7: Graph Results
# Heat Map Graph
plt.figure(figsize=(8, 8))
sns.heatmap(data.corr(), square=True, annot=True, cmap='RdYlGn')
plt.title('Heatmap for correlation between variables')
plt.xticks(rotation=45, ha='right')
plt.show()
# Create a bar plot of R2
plt.figure(figsize=(10, 6))
plt.bar(list(results_r2.keys()), list(results_r2.values()))
plt.title('R-squared Comparison of Regression Models')
plt.xlabel('Regression Models')
plt.ylabel('R-squared Value')
plt.ylim(0, 1)
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.show()
# Create a bar plot of RMSE
models = list(set(list(results_rmse_train.keys()) + list(results_rmse_test.keys()))) # Get unique model names
models.sort() # Sort models for better visualization
bar_width = 0.35 # Set bar width
indices = np.arange(len(models)) # Create an array of indices for each model
plt.figure(figsize=(12, 6))
plt.bar(indices - bar_width/2, [results_rmse_train.get(model, 0) for model in models], bar_width, label='Training RMSE')
plt.bar(indices + bar_width/2, [results_rmse_test.get(model, 0) for model in models], bar_width, label='Testing RMSE')
plt.xlabel('Regression Models')
plt.ylabel('Mean Squared Error Value')
plt.title('Training and Testing Mean Squared Error Comparison of Regression Models')
plt.xticks(indices, models, rotation=45, ha='right')
plt.legend()
plt.tight_layout()
plt.show()
