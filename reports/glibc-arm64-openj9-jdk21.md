---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:37:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 23-27 cores)</summary>

```
1792675952 27
1792675957 27
1792675962 27
1792675967 27
1792675972 27
1792675977 27
1792675982 27
1792675987 27
1792675992 27
1792675997 27
1792676002 27
1792676007 27
1792676012 27
1792676017 27
1792676022 27
1792676027 27
1792676032 27
1792676037 27
1792676042 27
1792676047 27
```
</details>

---

