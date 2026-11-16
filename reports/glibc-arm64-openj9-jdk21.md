---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 00:05:27 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 24-26 cores)</summary>

```
1794805274 24
1794805279 24
1794805284 24
1794805289 24
1794805294 24
1794805299 25
1794805304 25
1794805309 25
1794805314 26
1794805319 26
1794805324 26
1794805329 26
1794805334 26
1794805339 26
1794805344 26
1794805349 26
1794805354 26
1794805359 26
1794805364 26
1794805369 26
```
</details>

---

