---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 15:26:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 960 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 74-96 cores)</summary>

```
1787080969 76
1787080974 76
1787080979 76
1787080984 76
1787080989 76
1787080994 76
1787080999 76
1787081004 76
1787081009 76
1787081014 76
1787081019 76
1787081024 76
1787081029 76
1787081034 76
1787081039 96
1787081044 96
1787081049 96
1787081054 76
1787081059 76
1787081064 76
```
</details>

---

