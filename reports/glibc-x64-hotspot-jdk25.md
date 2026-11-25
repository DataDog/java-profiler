---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:18:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1795641232 41
1795641237 41
1795641242 41
1795641247 41
1795641252 51
1795641257 51
1795641262 51
1795641267 51
1795641272 51
1795641277 51
1795641282 51
1795641287 51
1795641292 51
1795641297 51
1795641302 51
1795641307 51
1795641312 51
1795641317 42
1795641322 42
1795641327 42
```
</details>

---

