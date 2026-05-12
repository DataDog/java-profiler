---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-12 06:45:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1778582463 62
1778582468 64
1778582473 64
1778582478 64
1778582483 64
1778582488 64
1778582493 64
1778582498 64
1778582503 64
1778582508 64
1778582513 64
1778582518 64
1778582523 64
1778582528 64
1778582533 64
1778582538 64
1778582543 64
1778582548 64
1778582553 64
1778582558 64
```
</details>

---

