---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 15:45:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1793129938 76
1793129943 76
1793129948 76
1793129953 76
1793129958 76
1793129963 76
1793129968 76
1793129973 76
1793129978 76
1793129983 76
1793129988 76
1793129993 76
1793129998 76
1793130003 76
1793130008 76
1793130013 76
1793130018 76
1793130023 76
1793130028 76
1793130033 74
```
</details>

---

