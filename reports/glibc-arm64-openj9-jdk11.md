---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:23:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778512719 64
1778512724 64
1778512729 64
1778512734 64
1778512739 64
1778512744 64
1778512749 64
1778512754 64
1778512759 64
1778512764 64
1778512769 64
1778512774 64
1778512779 64
1778512784 64
1778512789 64
1778512794 64
1778512799 64
1778512805 64
1778512810 64
1778512815 59
```
</details>

---

