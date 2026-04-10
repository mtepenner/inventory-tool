import React from 'react';

const Navbar = () => {
    return (
        <nav className="bg-blue-800 text-white shadow-md">
            <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
                <div className="flex justify-between h-16 items-center">
                    <div className="flex-shrink-0 flex items-center space-x-2">
                        <span className="text-2xl">📦</span>
                        <span className="font-bold text-xl tracking-tight">Inventory System</span>
                    </div>
                    <div>
                        <span className="text-sm bg-blue-700 px-3 py-1 rounded-full shadow-inner">
                            v2.0 Full-Stack
                        </span>
                    </div>
                </div>
            </div>
        </nav>
    );
};

export default Navbar;
