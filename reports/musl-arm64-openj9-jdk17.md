---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 04:47:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 41-64 cores)</summary>

```
1786437752 64
1786437757 64
1786437762 53
1786437767 53
1786437772 53
1786437777 53
1786437782 53
1786437787 53
1786437792 53
1786437797 53
1786437802 53
1786437807 53
1786437812 53
1786437817 53
1786437822 53
1786437827 53
1786437832 53
1786437837 53
1786437842 53
1786437847 53
```
</details>

---

