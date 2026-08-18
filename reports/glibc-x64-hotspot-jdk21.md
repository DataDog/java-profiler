---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 08:24:27 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1787055584 80
1787055589 80
1787055594 80
1787055599 80
1787055604 80
1787055609 80
1787055614 80
1787055619 80
1787055624 80
1787055629 78
1787055634 78
1787055639 78
1787055644 78
1787055649 78
1787055654 78
1787055659 80
1787055664 80
1787055669 80
1787055674 80
1787055679 80
```
</details>

---

