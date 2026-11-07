---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-07 00:04:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1794027618 16
1794027623 16
1794027628 16
1794027633 16
1794027638 16
1794027643 16
1794027648 16
1794027653 16
1794027658 16
1794027663 16
1794027668 16
1794027673 16
1794027678 16
1794027683 16
1794027688 16
1794027693 16
1794027698 16
1794027703 16
1794027708 16
1794027713 16
```
</details>

---

