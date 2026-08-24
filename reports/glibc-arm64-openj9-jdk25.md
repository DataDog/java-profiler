---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-24 08:55:31 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 24-31 cores)</summary>

```
1787575863 31
1787575868 26
1787575873 26
1787575878 24
1787575883 24
1787575888 24
1787575893 24
1787575898 24
1787575903 24
1787575908 24
1787575913 24
1787575918 29
1787575923 29
1787575928 29
1787575933 29
1787575938 29
1787575943 29
1787575948 29
1787575953 29
1787575958 29
```
</details>

---

