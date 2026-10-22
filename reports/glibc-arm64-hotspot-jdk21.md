---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 08:38:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 13 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1792672479 44
1792672484 44
1792672489 44
1792672494 48
1792672499 48
1792672504 48
1792672509 48
1792672514 48
1792672519 48
1792672524 48
1792672529 48
1792672534 48
1792672539 48
1792672544 48
1792672549 48
1792672554 48
1792672559 48
1792672564 48
1792672569 48
1792672574 48
```
</details>

---

