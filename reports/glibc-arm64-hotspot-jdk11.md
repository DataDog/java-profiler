---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 09:20:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 9-10 cores)</summary>

```
1791465243 10
1791465248 10
1791465253 10
1791465258 10
1791465263 10
1791465268 10
1791465273 10
1791465278 10
1791465283 10
1791465288 10
1791465293 10
1791465298 10
1791465303 10
1791465308 10
1791465313 10
1791465318 10
1791465323 10
1791465328 10
1791465333 10
1791465338 10
```
</details>

---

