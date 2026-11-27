---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 11:20:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1795796237 83
1795796242 85
1795796247 85
1795796252 85
1795796257 85
1795796262 85
1795796267 85
1795796272 85
1795796277 85
1795796282 85
1795796287 85
1795796292 85
1795796297 85
1795796302 85
1795796307 85
1795796312 85
1795796317 85
1795796322 85
1795796327 85
1795796332 85
```
</details>

---

