---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 12:24:44 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 67-77 cores)</summary>

```
1777479448 71
1777479453 71
1777479458 71
1777479463 71
1777479468 71
1777479473 71
1777479478 69
1777479483 69
1777479488 67
1777479493 67
1777479498 67
1777479503 69
1777479508 69
1777479513 71
1777479518 71
1777479523 77
1777479528 77
1777479533 77
1777479538 77
1777479543 77
```
</details>

---

