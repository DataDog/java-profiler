---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-08 14:27:51 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 12-16 cores)</summary>

```
1794165861 14
1794165866 14
1794165871 12
1794165876 12
1794165881 12
1794165886 12
1794165891 12
1794165896 14
1794165901 14
1794165906 14
1794165911 14
1794165916 12
1794165921 12
1794165926 12
1794165931 12
1794165936 12
1794165941 12
1794165946 12
1794165951 12
1794165956 12
```
</details>

---

