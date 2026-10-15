---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-15 03:56:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 80-96 cores)</summary>

```
1792050680 80
1792050685 80
1792050690 80
1792050695 80
1792050700 80
1792050705 80
1792050710 96
1792050715 96
1792050720 96
1792050725 96
1792050730 96
1792050735 96
1792050740 96
1792050745 96
1792050750 96
1792050755 96
1792050760 96
1792050765 96
1792050770 96
1792050775 96
```
</details>

---

