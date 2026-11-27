---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 17:07:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 5 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 8-17 cores)</summary>

```
1795817014 8
1795817019 8
1795817024 8
1795817029 8
1795817034 8
1795817039 8
1795817044 8
1795817049 8
1795817054 8
1795817059 8
1795817064 17
1795817069 17
1795817074 17
1795817079 17
1795817084 17
1795817089 17
1795817094 17
1795817099 17
1795817104 17
1795817109 17
```
</details>

---

