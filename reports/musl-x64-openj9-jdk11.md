---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:34:15 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1794580047 30
1794580052 30
1794580057 30
1794580062 30
1794580067 30
1794580072 30
1794580077 30
1794580082 30
1794580087 30
1794580092 30
1794580097 30
1794580102 30
1794580107 32
1794580112 32
1794580117 32
1794580122 32
1794580127 32
1794580132 32
1794580137 32
1794580142 32
```
</details>

---

