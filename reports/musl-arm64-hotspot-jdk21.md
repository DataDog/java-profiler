---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-13 06:34:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 7 |
| Allocations | 98 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 12-14 cores)</summary>

```
1786617036 14
1786617041 12
1786617046 12
1786617051 12
1786617056 12
1786617061 12
1786617066 12
1786617071 12
1786617076 12
1786617081 12
1786617086 12
1786617091 12
1786617096 12
1786617101 12
1786617106 12
1786617111 14
1786617116 14
1786617121 14
1786617126 14
1786617131 14
```
</details>

---

