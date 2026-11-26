---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:49:38 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795707903 33
1795707908 33
1795707913 33
1795707918 33
1795707923 33
1795707928 33
1795707933 33
1795707938 33
1795707943 33
1795707948 33
1795707953 33
1795707958 33
1795707963 33
1795707968 33
1795707973 33
1795707978 33
1795707983 33
1795707988 33
1795707993 33
1795707998 64
```
</details>

---

