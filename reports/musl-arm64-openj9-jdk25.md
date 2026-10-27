---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 15:45:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 14-48 cores)</summary>

```
1793129954 14
1793129959 14
1793129964 14
1793129969 14
1793129974 14
1793129979 14
1793129984 14
1793129989 14
1793129994 14
1793129999 14
1793130004 14
1793130009 14
1793130014 14
1793130019 14
1793130024 14
1793130029 14
1793130034 14
1793130039 14
1793130044 14
1793130050 48
```
</details>

---

