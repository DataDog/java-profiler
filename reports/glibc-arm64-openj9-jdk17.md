---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:58:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795452833 64
1795452838 64
1795452843 64
1795452848 64
1795452853 64
1795452858 64
1795452863 64
1795452868 64
1795452873 64
1795452878 64
1795452883 64
1795452888 64
1795452893 64
1795452898 64
1795452903 64
1795452908 64
1795452913 64
1795452918 64
1795452923 64
1795452928 64
```
</details>

---

