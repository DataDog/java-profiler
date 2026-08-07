---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 05:50:47 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 89-94 cores)</summary>

```
1786095956 89
1786095961 91
1786095966 91
1786095971 91
1786095976 91
1786095981 91
1786095986 91
1786095991 91
1786095996 91
1786096001 91
1786096006 94
1786096011 94
1786096016 94
1786096021 94
1786096026 94
1786096031 94
1786096036 94
1786096041 94
1786096046 94
1786096051 94
```
</details>

---

