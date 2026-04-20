---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:31:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776694912 64
1776694917 64
1776694922 64
1776694927 64
1776694932 64
1776694937 64
1776694942 64
1776694947 64
1776694952 64
1776694957 64
1776694962 64
1776694967 64
1776694972 64
1776694977 64
1776694982 64
1776694987 64
1776694992 64
1776694998 64
1776695003 64
1776695008 64
```
</details>

---

