---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-08 00:57:02 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 20-24 cores)</summary>

```
1786164761 20
1786164766 20
1786164771 20
1786164776 20
1786164781 20
1786164786 20
1786164791 20
1786164796 20
1786164801 24
1786164806 24
1786164811 24
1786164816 24
1786164821 24
1786164826 24
1786164831 24
1786164836 24
1786164841 24
1786164846 24
1786164851 24
1786164856 24
```
</details>

---

