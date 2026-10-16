---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 05:17:21 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 11 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 12 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1792141975 54
1792141980 54
1792141985 54
1792141990 64
1792141995 64
1792142000 64
1792142005 64
1792142010 64
1792142015 64
1792142020 64
1792142025 64
1792142030 64
1792142035 64
1792142040 64
1792142045 64
1792142050 64
1792142055 64
1792142060 64
1792142065 64
1792142070 64
```
</details>

---

