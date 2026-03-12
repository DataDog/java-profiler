---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-12 10:27:00 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 852 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 13 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1773325278 63
1773325283 63
1773325288 63
1773325293 63
1773325298 63
1773325303 63
1773325308 63
1773325313 63
1773325318 63
1773325323 63
1773325328 63
1773325333 63
1773325338 63
1773325343 63
1773325348 63
1773325353 61
1773325358 61
1773325363 63
1773325368 63
1773325373 63
```
</details>

---

