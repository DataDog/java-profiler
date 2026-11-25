---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:48:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 10 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 17-34 cores)</summary>

```
1795632227 18
1795632232 18
1795632237 18
1795632242 18
1795632247 18
1795632252 18
1795632257 18
1795632262 34
1795632267 34
1795632272 34
1795632277 34
1795632282 34
1795632287 34
1795632292 34
1795632297 34
1795632302 34
1795632307 34
1795632312 34
1795632317 34
1795632322 17
```
</details>

---

