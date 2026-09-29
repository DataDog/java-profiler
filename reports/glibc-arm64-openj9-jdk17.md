---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 11:52:32 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 8-28 cores)</summary>

```
1790696940 23
1790696945 23
1790696950 23
1790696955 23
1790696960 23
1790696965 23
1790696970 28
1790696975 28
1790696980 28
1790696985 28
1790696990 28
1790696995 28
1790697000 28
1790697005 28
1790697010 28
1790697015 28
1790697020 28
1790697025 28
1790697030 28
1790697035 28
```
</details>

---

