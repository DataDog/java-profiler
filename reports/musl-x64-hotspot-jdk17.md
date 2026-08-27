---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-27 09:40:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787837723 64
1787837728 64
1787837733 64
1787837738 64
1787837744 64
1787837749 64
1787837754 64
1787837759 64
1787837764 64
1787837769 64
1787837774 64
1787837779 64
1787837784 64
1787837789 64
1787837794 64
1787837799 64
1787837804 64
1787837809 64
1787837814 64
1787837819 66
```
</details>

---

