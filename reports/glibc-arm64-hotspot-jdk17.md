---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 07:02:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 27-35 cores)</summary>

```
1792666524 35
1792666529 35
1792666534 35
1792666539 35
1792666544 30
1792666549 30
1792666554 30
1792666559 30
1792666564 30
1792666569 30
1792666574 30
1792666579 30
1792666584 30
1792666589 30
1792666594 30
1792666599 30
1792666604 30
1792666609 30
1792666614 30
1792666619 30
```
</details>

---

