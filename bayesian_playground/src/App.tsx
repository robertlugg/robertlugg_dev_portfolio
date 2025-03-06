import Layout from './Layout';
import ErrorBoundary from './components/ErrorBoundary';

const App = () => (
  <ErrorBoundary>
    <Layout />
  </ErrorBoundary>
);

export default App;
