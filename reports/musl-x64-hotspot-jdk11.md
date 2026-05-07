---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 11:01:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1082 |
| Sample Rate | 18.03/sec |
| Health Score | 1127% |
| Threads | 11 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (4 unique values: 65-77 cores)</summary>

```
1778165861 73
1778165866 73
1778165871 73
1778165876 73
1778165881 73
1778165886 73
1778165891 73
1778165896 77
1778165901 77
1778165906 77
1778165911 77
1778165916 65
1778165921 65
1778165926 65
1778165931 65
1778165936 65
1778165941 65
1778165946 65
1778165951 65
1778165956 65
```
</details>

---

