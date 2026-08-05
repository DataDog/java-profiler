---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-05 08:26:01 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (4 unique values: 31-41 cores)</summary>

```
1785932498 38
1785932503 38
1785932508 38
1785932513 38
1785932518 38
1785932523 38
1785932528 31
1785932533 31
1785932538 31
1785932543 31
1785932548 31
1785932553 31
1785932558 39
1785932563 39
1785932568 39
1785932573 39
1785932578 41
1785932583 41
1785932588 41
1785932593 41
```
</details>

---

