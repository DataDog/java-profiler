---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:38:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1792672499 44
1792672504 44
1792672509 44
1792672514 44
1792672519 44
1792672524 44
1792672529 44
1792672534 44
1792672539 44
1792672544 44
1792672549 44
1792672554 44
1792672559 44
1792672564 44
1792672569 44
1792672574 44
1792672579 44
1792672584 48
1792672589 48
1792672594 48
```
</details>

---

