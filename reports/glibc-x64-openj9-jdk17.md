---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:18:51 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 49-55 cores)</summary>

```
1795605252 55
1795605257 55
1795605262 55
1795605267 55
1795605272 55
1795605277 55
1795605282 55
1795605287 55
1795605292 55
1795605297 55
1795605302 55
1795605307 55
1795605312 55
1795605317 55
1795605322 55
1795605327 55
1795605332 55
1795605337 55
1795605342 55
1795605347 53
```
</details>

---

