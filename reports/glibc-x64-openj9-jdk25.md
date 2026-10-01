---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 09:06:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 40-55 cores)</summary>

```
1790859764 40
1790859769 40
1790859774 40
1790859779 40
1790859784 40
1790859789 42
1790859794 42
1790859799 55
1790859804 55
1790859809 55
1790859814 55
1790859819 55
1790859824 55
1790859829 53
1790859834 53
1790859839 53
1790859844 53
1790859849 55
1790859854 55
1790859859 55
```
</details>

---

