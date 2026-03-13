---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-13 05:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 11 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 12 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 24-42 cores)</summary>

```
1773394728 24
1773394733 24
1773394738 24
1773394743 33
1773394748 33
1773394753 33
1773394758 42
1773394763 42
1773394768 42
1773394774 42
1773394779 42
1773394784 42
1773394789 42
1773394794 42
1773394799 42
1773394804 42
1773394809 42
1773394814 42
1773394819 42
1773394824 42
```
</details>

---

