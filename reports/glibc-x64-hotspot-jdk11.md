---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 945 |
| Sample Rate | 15.75/sec |
| Health Score | 984% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1788530843 71
1788530848 71
1788530853 71
1788530858 71
1788530863 71
1788530868 71
1788530873 71
1788530878 71
1788530883 71
1788530888 71
1788530893 71
1788530898 71
1788530903 71
1788530908 79
1788530913 79
1788530918 79
1788530923 79
1788530928 79
1788530933 79
1788530938 79
```
</details>

---

