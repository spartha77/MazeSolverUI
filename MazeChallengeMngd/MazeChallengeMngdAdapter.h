using namespace System::Collections::Generic;


namespace MazeChallengeAdapterNS
{

    public ref class MazeUtils
    {
    };
    public ref class Cell
    {
    private:
        int m_Row = -1, m_Col = -1;
    public:
        Cell(int row, int col)
        {
            m_Row = row;
            m_Col = col;
        }
        property int Row
        {
            int get()
            {
                return m_Row;
            }
            void set(int value)
            {
                m_Row = value;
            }
        }
        property int Col
        {
            int get()
            {
                return m_Col;
            }
            void set(int value)
            {
                m_Col = value;
            }
        }
    };
    public ref class Path
    {
    public:
        List<Cell^>^ m_SolutionPath;
    };

    public ref class Paths
    {
    public:
        List<Path^>^ m_SolutionPath;
    };

    public ref class MazeSolverMngdAdapter
    {
    private:
        bool m_ContainsCycles = false;
    public:
        int m_Rows = 0;
        int m_Cols = 0;
        List<List<int>^>^ m_MazeMatrix;
        void CreateGraph(System::String^ mngdFilename);
        //void PlanPathUsingDFS(Path^ path);
        List<List<Cell^>^>^ FindPathUsingDFS(int row, int col);
        List<List<Cell^>^>^ FindPathUsingNonGreedyASTAR(int st_row, int st_col, int end_row, int end_col);
        property bool ContainsCycles
        {
            bool get()
            {
                return m_ContainsCycles;
            }
        }

    };

    
    
    

    
};
