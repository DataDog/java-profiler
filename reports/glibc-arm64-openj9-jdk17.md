---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 08:23:42 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790165940 36
1790165945 36
1790165950 36
1790165955 48
1790165960 48
1790165965 48
1790165970 48
1790165975 48
1790165980 48
1790165985 48
1790165990 48
1790165995 48
1790166000 48
1790166005 48
1790166010 48
1790166015 48
1790166020 48
1790166025 48
1790166030 48
1790166035 48
```
</details>

---

