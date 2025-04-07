import './globals.css'

export const metadata = {
  title: 'Constitution of India Analysis Platform',
  description: 'A platform for analyzing and visualizing the Constitution of India dataset',
}

export default function RootLayout({ children }) {
  return (
    <html lang="en">
      <body>{children}</body>
    </html>
  )
} 