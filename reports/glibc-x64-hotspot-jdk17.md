---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 11:40:11 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 86-90 cores)</summary>

```
1795192453 90
1795192458 89
1795192463 89
1795192468 86
1795192473 86
1795192478 86
1795192483 86
1795192488 86
1795192493 88
1795192498 88
1795192503 88
1795192508 88
1795192513 88
1795192518 88
1795192524 88
1795192529 88
1795192534 88
1795192539 88
1795192544 88
1795192549 88
```
</details>

---

