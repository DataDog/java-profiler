---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:30:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790090689 22
1790090694 22
1790090699 22
1790090704 22
1790090709 22
1790090714 22
1790090719 22
1790090724 22
1790090729 22
1790090734 22
1790090739 22
1790090744 22
1790090749 22
1790090754 22
1790090759 22
1790090764 22
1790090769 22
1790090774 22
1790090779 22
1790090784 22
```
</details>

---

