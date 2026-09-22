---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:30:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 990 |
| Sample Rate | 16.50/sec |
| Health Score | 1031% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 65-94 cores)</summary>

```
1790090689 94
1790090694 86
1790090699 86
1790090704 86
1790090709 65
1790090714 65
1790090719 65
1790090724 65
1790090729 65
1790090734 65
1790090739 65
1790090744 65
1790090749 65
1790090754 65
1790090759 65
1790090764 65
1790090769 65
1790090774 65
1790090779 65
1790090785 65
```
</details>

---

