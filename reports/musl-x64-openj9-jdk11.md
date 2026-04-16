---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 05:53:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 57-64 cores)</summary>

```
1776332851 64
1776332856 64
1776332861 64
1776332866 64
1776332871 64
1776332876 62
1776332881 62
1776332886 62
1776332891 62
1776332896 62
1776332901 62
1776332906 62
1776332911 62
1776332916 62
1776332921 62
1776332926 62
1776332931 62
1776332936 62
1776332941 62
1776332946 62
```
</details>

---

