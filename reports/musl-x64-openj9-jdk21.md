---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:52:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 50-59 cores)</summary>

```
1790174714 50
1790174719 50
1790174724 50
1790174729 50
1790174734 50
1790174739 50
1790174744 50
1790174749 50
1790174754 50
1790174759 59
1790174764 59
1790174769 59
1790174774 59
1790174779 59
1790174784 59
1790174789 59
1790174794 59
1790174799 59
1790174804 59
1790174809 59
```
</details>

---

