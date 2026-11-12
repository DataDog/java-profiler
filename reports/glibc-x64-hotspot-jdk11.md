---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:47:07 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794487352 32
1794487357 32
1794487362 32
1794487367 32
1794487372 32
1794487377 32
1794487382 32
1794487387 32
1794487392 32
1794487397 32
1794487402 32
1794487407 32
1794487412 32
1794487417 32
1794487422 32
1794487427 32
1794487432 32
1794487437 32
1794487442 32
1794487447 32
```
</details>

---

