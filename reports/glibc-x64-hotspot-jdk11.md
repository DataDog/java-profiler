---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-07 18:05:06 EST

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
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 29-50 cores)</summary>

```
1794092426 29
1794092431 29
1794092436 29
1794092441 33
1794092446 33
1794092451 33
1794092456 33
1794092461 33
1794092466 33
1794092471 33
1794092476 33
1794092481 33
1794092486 33
1794092491 33
1794092496 33
1794092501 50
1794092506 50
1794092511 50
1794092516 50
1794092521 50
```
</details>

---

