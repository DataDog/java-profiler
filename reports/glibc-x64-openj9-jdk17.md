---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-06 04:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1772790232 53
1772790237 53
1772790242 53
1772790247 53
1772790252 53
1772790257 53
1772790262 53
1772790267 53
1772790272 53
1772790277 48
1772790282 48
1772790287 48
1772790292 48
1772790297 48
1772790302 48
1772790307 48
1772790312 48
1772790317 48
1772790322 48
1772790327 48
```
</details>

---

