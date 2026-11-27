---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 17:07:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 12-21 cores)</summary>

```
1795817014 12
1795817019 12
1795817024 12
1795817029 12
1795817034 12
1795817040 12
1795817045 12
1795817050 12
1795817055 12
1795817060 12
1795817065 12
1795817070 12
1795817075 12
1795817080 12
1795817085 12
1795817090 21
1795817095 21
1795817100 21
1795817105 21
1795817110 21
```
</details>

---

