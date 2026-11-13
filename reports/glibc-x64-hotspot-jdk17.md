---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:25:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 53-60 cores)</summary>

```
1794583241 55
1794583246 55
1794583251 55
1794583256 55
1794583261 55
1794583266 55
1794583271 55
1794583276 55
1794583281 53
1794583286 53
1794583291 53
1794583296 53
1794583301 53
1794583306 53
1794583311 53
1794583316 53
1794583321 53
1794583326 60
1794583331 60
1794583336 60
```
</details>

---

