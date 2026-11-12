---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 14:30:58 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 15 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (8 unique values: 37-46 cores)</summary>

```
1794511605 45
1794511610 45
1794511615 46
1794511620 46
1794511625 44
1794511630 44
1794511635 44
1794511640 45
1794511645 45
1794511650 44
1794511655 44
1794511660 39
1794511665 39
1794511670 42
1794511675 42
1794511680 42
1794511685 40
1794511690 40
1794511695 39
1794511700 39
```
</details>

---

