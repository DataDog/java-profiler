---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 05:50:05 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1022 |
| Sample Rate | 17.03/sec |
| Health Score | 1064% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1790675081 44
1790675086 44
1790675091 44
1790675096 44
1790675101 44
1790675106 39
1790675111 39
1790675116 39
1790675121 39
1790675126 39
1790675131 39
1790675136 39
1790675141 39
1790675146 39
1790675151 39
1790675156 39
1790675161 39
1790675166 39
1790675171 39
1790675176 39
```
</details>

---

