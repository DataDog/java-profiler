---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:49:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1795707878 16
1795707883 16
1795707888 16
1795707893 16
1795707898 16
1795707903 16
1795707908 16
1795707913 16
1795707918 16
1795707923 16
1795707928 16
1795707933 16
1795707938 16
1795707943 16
1795707948 16
1795707953 16
1795707958 16
1795707963 16
1795707968 16
1795707973 16
```
</details>

---

