---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 912 |
| Sample Rate | 15.20/sec |
| Health Score | 950% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (5 unique values: 67-78 cores)</summary>

```
1777558034 67
1777558039 67
1777558044 67
1777558049 67
1777558054 67
1777558059 67
1777558064 67
1777558069 67
1777558074 67
1777558079 67
1777558084 72
1777558089 72
1777558094 72
1777558099 72
1777558104 76
1777558109 76
1777558114 78
1777558119 78
1777558124 78
1777558129 78
```
</details>

---

