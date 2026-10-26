---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 12:41:44 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 85-89 cores)</summary>

```
1793032667 89
1793032672 89
1793032677 89
1793032682 89
1793032687 89
1793032692 89
1793032697 89
1793032702 89
1793032707 87
1793032712 87
1793032717 87
1793032722 85
1793032727 85
1793032732 85
1793032737 85
1793032742 85
1793032747 85
1793032752 85
1793032757 88
1793032762 88
```
</details>

---

