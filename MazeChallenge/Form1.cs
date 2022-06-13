using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using System.Windows.Automation;
using System.Diagnostics;
using System.Runtime.InteropServices;
using MazeChallengeAdapterNS;

namespace MazeChallenge
{   
    public partial class Form1 : Form
    {

        [DllImport("user32.dll", EntryPoint = "FindWindow", SetLastError = true)]
        static extern IntPtr FindWindowByCaption(IntPtr ZeroOnly, string lpWindowName);

        [DllImport("user32.Dll")]
        static extern int PostMessage(IntPtr hWnd, UInt32 msg, int wParam, int lParam);

        const UInt32 WM_CLOSE = 0x0010;

        int m_Rows = 0;
        int m_Cols = 0;
        String m_MazeFileName;
        public List<List<int>> m_MazeMatrix;
        MazeChallengeAdapterNS.MazeSolverMngdAdapter m_MazeSolverMngdAdapter;
        MazeChallengeAdapterNS.Cell m_StartCell = null, m_EndCell = null;
        Thread m_Thread;
        InputState m_InputState = InputState.NULL;
        Solver m_Solver = Solver.NULL;

        List<List<Cell>> m_SolutionPaths;
         
        public Form1()
        {
            InitializeComponent();
            this.depthFirstSearchToolStripMenuItem.Enabled = false;
            this.nonGreedyAToolStripMenuItem.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            if (m_Rows != 0 && m_Cols != 0)
                InitializeMaze();
            m_MazeSolverMngdAdapter = new MazeChallengeAdapterNS.MazeSolverMngdAdapter();
            m_SolutionPaths = null;
            //formatCell(5, 5);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Solved by Parthasarathy Srinivasan", "Maze Solver");
        }

        private void InitializeMaze()
        {
            mazeBlocksDataGrid.BackgroundColor = Color.Black;
            mazeBlocksDataGrid.DefaultCellStyle.BackColor = Color.Black;
            mazeBlocksDataGrid.Columns.Clear();
            

            for (int ii = 0; ii < m_Cols; ii++)
            {
                mazeBlocksDataGrid.Columns.Add("", "");
            }

            for (int ii = 0; ii < m_Rows; ii++)
            {
                mazeBlocksDataGrid.Rows.Add();
            }

           
            foreach (DataGridViewColumn col in mazeBlocksDataGrid.Columns)
            {
                col.Width = mazeBlocksDataGrid.Width / mazeBlocksDataGrid.Columns.Count;
            }

            foreach (DataGridViewRow row in mazeBlocksDataGrid.Rows)
            {
                row.Height = mazeBlocksDataGrid.Height / mazeBlocksDataGrid.Rows.Count;
            }

            // Make each cell readonly
            for (int row = 0; row < mazeBlocksDataGrid.Rows.Count; row++)
            {
                for (int col = 0; col < mazeBlocksDataGrid.Columns.Count; col++)
                {
                    mazeBlocksDataGrid[col, row].ReadOnly = true;
                    mazeBlocksDataGrid[col, row].Tag = "";

                    if (m_MazeMatrix[row][col] == 1)
                    {
                        mazeBlocksDataGrid[col, row].Style.BackColor = Color.Orange;
                        mazeBlocksDataGrid[col, row].Tag = "F";
                    }
                    else
                    {
                        mazeBlocksDataGrid[col, row].Style.BackColor = Color.Black;
                        mazeBlocksDataGrid[col, row].Tag = "B";
                    }
                    mazeBlocksDataGrid.MultiSelect = true;
                }
            }

            int count = 0;
            if (m_SolutionPaths != null)
            {
                foreach (var path in m_SolutionPaths)
                {
                    if (count == 0)
                    {
                        foreach (var cellCoord in path)
                        {
                            mazeBlocksDataGrid[cellCoord.Col, cellCoord.Row].Style.BackColor = Color.Green;
                            mazeBlocksDataGrid[cellCoord.Col, cellCoord.Row].Tag = "F"; //Feasible
                        }
                    }
                    count++;
                }
            }
            // Unselect the default selection at 0,0 to none
            this.mazeBlocksDataGrid.Rows[0].Cells[0].Selected = false;

            this.mazeBlocksDataGrid.ReadOnly = true;
        }

       
        private bool StateManageAndExecute(Solver solver)
        {
            String caption, text;
            if (m_InputState == InputState.NULL)
            {
                MessageBox.Show
                (
                  "No maze loaded. First open any maze",
                  "DFS Solver",
                  MessageBoxButtons.OK,
                  MessageBoxIcon.Error
                );
                return false;
            }
            else if (m_InputState == InputState.MazeLoaded)
            {
                CloseMessageBox("Depth First Search");
                CloseMessageBox("Non-greedy A*");
                CloseMessageBox("Cycles Detected");

                text = "Select Orange colored starting cell of the maze";
                if (solver == Solver.DFS)
                {
                    caption = "Depth First Search";
                }
                else
                {
                    caption = "Non-greedy A*";
                }

                this.m_Thread = new Thread(new ThreadStart(delegate
                {
                    MessageBox.Show
                    (
                      text,
                      caption,
                      MessageBoxButtons.OK,
                      MessageBoxIcon.Information
                    );
                }));
                this.m_Thread.Start();
                return false;
            }
            else if (m_InputState == InputState.StartCellSelected)
            {   
                CloseMessageBox("Non-greedy A*");
                CloseMessageBox("Cycles Detected");
                

                if (solver == Solver.DFS)
                {
                    // Call Solver
                    return true;
                }
                else
                {
                    caption = "Non-greedy A*";
                    text = "Select Orange colored ending cell of the maze";

                    this.m_Thread = new Thread(new ThreadStart(delegate
                    {
                        MessageBox.Show
                        (
                          text,
                          caption,
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Information
                        );
                    }));
                    this.m_Thread.Start();
                    return false;
                }
            }
            else if (m_Solver == Solver.NonGreedyASTAR && m_InputState == InputState.EndCellSelected)
            {
                // call solver
                return true;
            }

            return false;
        }
        private void depthFirstSearchToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_Solver = Solver.DFS;
            this.mazeBlocksDataGrid.ClearSelection();
            this.StateManageAndExecute(m_Solver);
            m_StartCell = null;
            m_EndCell = null;
            this.m_InputState = InputState.MazeLoaded;
            m_SolutionPaths = null;
            InitializeMaze();
        }

        private void nonGreedyAToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.mazeBlocksDataGrid.ClearSelection();
            this.m_Solver = Solver.NonGreedyASTAR;
            this.StateManageAndExecute(m_Solver);
            m_StartCell = null;
            m_EndCell = null;
            this.m_InputState = InputState.MazeLoaded;
            m_SolutionPaths = null;
            InitializeMaze();
        }



        private void openMazeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Open the OpenFileDialog and make the user select the maze file
            this.openMazeFileDialog.ShowDialog();
        }

        private void openMazeFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            this.m_InputState = InputState.NULL;
            this.m_MazeFileName = this.openMazeFileDialog.FileName;
            this.m_MazeSolverMngdAdapter.CreateGraph(this.m_MazeFileName);
            this.m_Rows = this.m_MazeSolverMngdAdapter.m_Rows;
            this.m_Cols = this.m_MazeSolverMngdAdapter.m_Cols;
            this.m_MazeMatrix = this.m_MazeSolverMngdAdapter.m_MazeMatrix;
            this.m_SolutionPaths = null;
            if (this.m_MazeMatrix.Count > 0)
            {
                this.m_InputState = InputState.MazeLoaded;

                this.depthFirstSearchToolStripMenuItem.Enabled = true;
                this.nonGreedyAToolStripMenuItem.Enabled = true;
            }

            InitializeMaze();
        }

        private void mazeBlocksDataGrid_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            
            int rowSelected = e.RowIndex;
            int colSelected = e.ColumnIndex;
            DataGridViewCell cell = mazeBlocksDataGrid[colSelected, rowSelected];
            if (cell.Tag == null)
                cell.Tag = "";
            if (m_MazeMatrix[rowSelected][colSelected] == 1)
            {
                mazeBlocksDataGrid[colSelected, rowSelected].Style.BackColor = Color.Orange;
                mazeBlocksDataGrid[colSelected, rowSelected].Tag = "F"; //Feasible
            }
            else
            {
                mazeBlocksDataGrid[colSelected, rowSelected].Style.BackColor = Color.Black;
                mazeBlocksDataGrid[colSelected, rowSelected].Tag = "B"; //Blocked
            }

            if (m_Solver == Solver.NULL)
                return;

            if ( mazeBlocksDataGrid[colSelected, rowSelected].Tag == "B" )
            {
                this.mazeBlocksDataGrid.ClearSelection();
                this.CloseMessageBox("Depth First Search");
                this.CloseMessageBox("Non-greedy A*");
                CloseMessageBox("Cycles Detected");

                MessageBox.Show
                        (
                          "The cell selected is not valid/feasible. Select Orange colored feasible cell",
                          "Error in Cell Selection",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Error
                        );
                

                return;
            }
            else if (m_Solver == Solver.DFS)
            {
                m_StartCell = new MazeChallengeAdapterNS.Cell(rowSelected, colSelected);
                m_InputState = InputState.StartCellSelected;
            }
            else if (m_Solver == Solver.NonGreedyASTAR)
            {
                if ( m_StartCell == null )
                {
                    m_InputState = InputState.StartCellSelected;
                    m_StartCell = new MazeChallengeAdapterNS.Cell(rowSelected, colSelected);
                }
                else 
                {
                    m_InputState = InputState.EndCellSelected;
                    m_EndCell = new MazeChallengeAdapterNS.Cell(rowSelected, colSelected);
                }
            }
            bool containsCycles = false;
            if ( StateManageAndExecute(m_Solver) )
            {
                this.mazeBlocksDataGrid.ClearSelection();
                
                CloseMessageBox("Depth First Search");
                CloseMessageBox("Non-greedy A*");
                CloseMessageBox("Cycles Detected");

                MazeChallengeAdapterNS.Paths allPaths = new MazeChallengeAdapterNS.Paths();

                if ( m_Solver == Solver.DFS )
                    m_SolutionPaths = this.m_MazeSolverMngdAdapter.FindPathUsingDFS(m_StartCell.Row, m_StartCell.Col);
                else if ( m_Solver == Solver.NonGreedyASTAR)
                    m_SolutionPaths = this.m_MazeSolverMngdAdapter.FindPathUsingNonGreedyASTAR(m_StartCell.Row, m_StartCell.Col, m_EndCell.Row, m_EndCell.Col);
                this.m_InputState = InputState.MazeLoaded;
                this.m_Solver = Solver.NULL;
                containsCycles = this.m_MazeSolverMngdAdapter.ContainsCycles;
                
            }
            int count = 0;
            if (m_SolutionPaths != null)
            {
                foreach (var path in m_SolutionPaths)
                {
                    if (count == 0)
                    {
                        foreach (var cellCoord in path)
                        {
                            mazeBlocksDataGrid[cellCoord.Col, cellCoord.Row].Style.BackColor = Color.Green;
                            mazeBlocksDataGrid[cellCoord.Col, cellCoord.Row].Tag = "F"; //Feasible
                        }
                    }
                    count++;
                }
            }

            if (containsCycles)
            {
                String text = "The maze has one or more cycles!";
                String caption = "Cycles Detected";

                MessageBox.Show
                (
                  text,
                  caption,
                  MessageBoxButtons.OK,
                  MessageBoxIcon.Warning
                );

            }


        }
        public enum InputState
        {
            NULL, MazeLoaded, StartCellSelected, EndCellSelected
        }

        public enum Solver
        {
            NULL, DFS, NonGreedyASTAR
        }

        void CloseMessageBox(String caption)
        {
            IntPtr hWnd = FindWindowByCaption(IntPtr.Zero, caption);
            if (hWnd != IntPtr.Zero)
            {
                PostMessage(hWnd, WM_CLOSE, 0, 0);
                if (m_Thread.IsAlive)
                    m_Thread.Abort();
            }
        }
        
    }
}
