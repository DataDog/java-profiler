---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:01:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 968 |
| Sample Rate | 16.13/sec |
| Health Score | 1008% |
| Threads | 10 |
| Allocations | 567 |

<details>
<summary>CPU Timeline (2 unique values: 29-33 cores)</summary>

```
1795625853 33
1795625858 33
1795625863 33
1795625868 33
1795625873 33
1795625878 29
1795625883 29
1795625888 29
1795625893 29
1795625898 29
1795625903 29
1795625908 29
1795625913 29
1795625918 29
1795625923 29
1795625928 29
1795625933 29
1795625938 29
1795625943 29
1795625948 29
```
</details>

---

