---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 16:30:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 6 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776975931 64
1776975936 64
1776975941 64
1776975946 64
1776975951 64
1776975956 64
1776975961 64
1776975966 64
1776975971 64
1776975976 64
1776975981 64
1776975986 64
1776975991 64
1776975996 64
1776976001 64
1776976006 64
1776976011 64
1776976016 64
1776976021 64
1776976026 64
```
</details>

---

