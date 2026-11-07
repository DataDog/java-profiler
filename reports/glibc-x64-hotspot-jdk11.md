---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 22:03:12 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 43-60 cores)</summary>

```
1794020206 49
1794020211 49
1794020216 43
1794020221 43
1794020226 43
1794020231 43
1794020236 43
1794020241 43
1794020246 43
1794020251 43
1794020256 43
1794020261 43
1794020266 43
1794020271 43
1794020276 43
1794020281 43
1794020286 43
1794020291 43
1794020296 60
1794020301 60
```
</details>

---

