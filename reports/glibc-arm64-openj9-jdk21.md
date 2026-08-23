---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-23 05:47:30 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 11 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787478234 59
1787478239 59
1787478244 59
1787478249 64
1787478254 64
1787478259 64
1787478264 64
1787478269 64
1787478274 64
1787478279 64
1787478284 64
1787478289 64
1787478294 64
1787478299 64
1787478304 64
1787478309 64
1787478314 64
1787478319 64
1787478324 64
1787478329 64
```
</details>

---

