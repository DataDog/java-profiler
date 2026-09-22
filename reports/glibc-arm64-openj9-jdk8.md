---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 11:30:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 278 |
| Sample Rate | 4.63/sec |
| Health Score | 289% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 24-26 cores)</summary>

```
1790090648 25
1790090653 25
1790090658 25
1790090663 25
1790090668 25
1790090673 25
1790090678 25
1790090683 25
1790090688 25
1790090693 25
1790090699 25
1790090704 25
1790090709 25
1790090714 25
1790090719 24
1790090724 24
1790090729 24
1790090734 24
1790090739 24
1790090744 24
```
</details>

---

