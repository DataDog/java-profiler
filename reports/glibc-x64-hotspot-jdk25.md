---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:58:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (4 unique values: 62-69 cores)</summary>

```
1778165579 62
1778165584 62
1778165589 62
1778165594 62
1778165599 64
1778165604 64
1778165609 62
1778165614 62
1778165619 62
1778165624 62
1778165629 62
1778165634 62
1778165639 62
1778165644 67
1778165649 67
1778165654 67
1778165659 67
1778165664 69
1778165669 69
1778165674 69
```
</details>

---

