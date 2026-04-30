---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 09:02:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (5 unique values: 59-78 cores)</summary>

```
1777553863 62
1777553868 62
1777553873 62
1777553878 62
1777553883 62
1777553888 62
1777553893 62
1777553898 62
1777553903 62
1777553908 62
1777553913 62
1777553918 62
1777553923 62
1777553928 62
1777553933 59
1777553938 59
1777553943 59
1777553948 59
1777553953 78
1777553958 78
```
</details>

---

