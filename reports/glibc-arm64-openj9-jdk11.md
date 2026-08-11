---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 10:11:25 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 11 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 14 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786457220 27
1786457225 27
1786457230 27
1786457235 27
1786457240 27
1786457245 27
1786457250 27
1786457255 27
1786457260 27
1786457265 27
1786457270 27
1786457275 32
1786457280 32
1786457285 32
1786457290 32
1786457295 32
1786457300 32
1786457305 32
1786457310 32
1786457315 32
```
</details>

---

