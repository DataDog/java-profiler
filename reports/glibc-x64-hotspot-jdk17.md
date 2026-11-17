---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 12:52:29 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 44-66 cores)</summary>

```
1794937496 44
1794937501 44
1794937506 44
1794937511 44
1794937516 44
1794937521 44
1794937526 44
1794937531 66
1794937536 66
1794937541 66
1794937546 66
1794937551 66
1794937556 66
1794937561 55
1794937566 55
1794937571 55
1794937576 55
1794937581 55
1794937586 55
1794937591 55
```
</details>

---

