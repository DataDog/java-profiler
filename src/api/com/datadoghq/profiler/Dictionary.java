package com.datadoghq.profiler;

import java.util.Arrays;
import java.util.concurrent.atomic.AtomicIntegerFieldUpdater;
import java.util.concurrent.atomic.AtomicReferenceArray;
import java.util.concurrent.atomic.AtomicReferenceFieldUpdater;
import java.util.function.IntSupplier;

/** Maps text to an integer encoding. Adapted from async-profiler. */
public class Dictionary {

    public Dictionary(ConstantConsumer consumer) {
        this.consumer = consumer;
    }

    @FunctionalInterface
    public interface ConstantConsumer {
        void accept(String key, int encoding);
    }

    private static final int ROW_BITS = 7;
    private static final int ROWS = (1 << ROW_BITS);
    private static final int CELLS = 3;
    private static final int TABLE_CAPACITY = (ROWS * CELLS);

    private final ConstantConsumer consumer;

    private final Table table = new Table(nextBaseIndex());

    private static final AtomicIntegerFieldUpdater<Dictionary> BASE_INDEX_UPDATER =
            AtomicIntegerFieldUpdater.newUpdater(Dictionary.class, "baseIndex");
    volatile int baseIndex;

    public int encode(String key) {
        Table table = this.table;
        int hash = key.hashCode();
        while (true) {
            int rowIndex = Math.abs(hash) % ROWS;
            Row row = table.rows[rowIndex];
            for (int c = 0; c < CELLS; c++) {
                String storedKey = row.keys.get(c);
                if (storedKey == null) {
                    if (row.keys.compareAndSet(c, null, key)) {
                        int index = table.index(rowIndex, c);
                        consumer.accept(key, index);
                        return index;
                    } else {
                        storedKey = row.keys.get(c);
                        if (key.equals(storedKey)) {
                            return table.index(rowIndex, c);
                        }
                    }
                }
                if (key.equals(storedKey)) {
                    return table.index(rowIndex, c);
                }
            }
            table = row.getOrCreateNextTable(this::nextBaseIndex);
            hash = Integer.rotateRight(hash, ROW_BITS);
        }
    }

    private int nextBaseIndex() {
        return BASE_INDEX_UPDATER.addAndGet(this, TABLE_CAPACITY);
    }

    private static final class Row {

        private static final AtomicReferenceFieldUpdater<Dictionary.Row, Dictionary.Table>
                NEXT_TABLE_UPDATER = AtomicReferenceFieldUpdater.newUpdater(Row.class, Table.class, "next");
        private final AtomicReferenceArray<String> keys = new AtomicReferenceArray<>(CELLS);
        volatile Table next;

        public Table getOrCreateNextTable(IntSupplier baseIndexSupplier) {
            Table next = this.next;
            if (next == null) {
                Table newTable = new Table(baseIndexSupplier.getAsInt());
                if (NEXT_TABLE_UPDATER.compareAndSet(this, null, newTable)) {
                    next = newTable;
                }
            }
            return next;
        }
    }

    private static final class Table {

        final Row[] rows;
        final int baseIndex;

        private Table(int baseIndex) {
            this.baseIndex = baseIndex;
            this.rows = new Row[ROWS];
            Arrays.setAll(rows, i -> new Row());
        }

        int index(int row, int col) {
            return baseIndex + (col << ROW_BITS) + row;
        }
    }
}
