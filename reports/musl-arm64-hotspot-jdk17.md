---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-27 09:40:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (4 unique values: 57-62 cores)</summary>

```
1787837719 59
1787837724 59
1787837729 59
1787837734 59
1787837739 59
1787837744 59
1787837749 57
1787837754 57
1787837759 59
1787837764 59
1787837769 59
1787837774 59
1787837779 59
1787837784 59
1787837789 62
1787837794 62
1787837799 62
1787837804 57
1787837809 57
1787837814 57
```
</details>

---

