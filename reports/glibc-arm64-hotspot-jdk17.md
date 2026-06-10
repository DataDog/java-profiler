---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-06-10 05:13:36 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1781082608 60
1781082613 60
1781082618 60
1781082623 60
1781082628 60
1781082633 60
1781082638 60
1781082643 60
1781082648 60
1781082653 60
1781082658 60
1781082663 64
1781082668 64
1781082673 64
1781082678 64
1781082683 64
1781082688 64
1781082693 64
1781082698 64
1781082703 64
```
</details>

---

