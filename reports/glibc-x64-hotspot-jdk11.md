---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 05:15:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 23-31 cores)</summary>

```
1795514992 29
1795514997 29
1795515002 31
1795515007 31
1795515012 31
1795515017 31
1795515022 31
1795515027 31
1795515032 31
1795515037 31
1795515042 23
1795515047 23
1795515052 23
1795515057 23
1795515062 23
1795515067 23
1795515072 23
1795515077 25
1795515082 25
1795515087 25
```
</details>

---

