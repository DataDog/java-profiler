---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 09:06:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1790859763 52
1790859769 52
1790859774 52
1790859779 52
1790859784 52
1790859789 52
1790859794 52
1790859799 52
1790859804 52
1790859809 52
1790859814 52
1790859819 52
1790859824 52
1790859829 52
1790859834 52
1790859839 52
1790859844 52
1790859849 52
1790859854 52
1790859859 52
```
</details>

---

