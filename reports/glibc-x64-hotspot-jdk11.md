---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 11:32:04 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1794846383 92
1794846388 92
1794846393 90
1794846398 90
1794846403 90
1794846408 90
1794846413 90
1794846418 90
1794846423 90
1794846428 90
1794846433 90
1794846438 90
1794846443 90
1794846448 90
1794846453 90
1794846458 90
1794846463 90
1794846468 90
1794846473 90
1794846478 90
```
</details>

---

