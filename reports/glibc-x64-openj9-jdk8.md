---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:01:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 53-58 cores)</summary>

```
1793184704 53
1793184709 53
1793184714 53
1793184719 53
1793184724 53
1793184729 53
1793184734 53
1793184739 53
1793184744 53
1793184749 55
1793184754 55
1793184759 55
1793184764 55
1793184769 55
1793184774 55
1793184779 55
1793184785 55
1793184790 55
1793184795 55
1793184800 58
```
</details>

---

