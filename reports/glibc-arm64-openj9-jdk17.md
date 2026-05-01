---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-01 09:14:16 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1777640932 54
1777640937 54
1777640942 54
1777640947 54
1777640952 54
1777640957 54
1777640962 54
1777640967 54
1777640972 54
1777640977 54
1777640982 54
1777640987 54
1777640992 49
1777640997 49
1777641002 49
1777641007 49
1777641012 49
1777641017 49
1777641022 49
```
</details>

---

