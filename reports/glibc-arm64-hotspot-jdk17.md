---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 09:35:56 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1792675569 18
1792675574 18
1792675579 18
1792675584 18
1792675589 18
1792675594 18
1792675599 18
1792675604 18
1792675609 18
1792675614 18
1792675619 18
1792675624 18
1792675629 18
1792675634 16
1792675639 16
1792675644 16
1792675649 16
1792675654 16
1792675659 16
1792675664 16
```
</details>

---

