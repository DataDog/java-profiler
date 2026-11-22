---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 16:32:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 54-87 cores)</summary>

```
1795382908 54
1795382913 54
1795382918 54
1795382923 54
1795382928 87
1795382933 87
1795382938 87
1795382943 87
1795382948 87
1795382953 87
1795382958 87
1795382963 87
1795382968 87
1795382973 87
1795382978 87
1795382983 87
1795382988 87
1795382993 87
1795382998 87
1795383003 87
```
</details>

---

