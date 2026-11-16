---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 20:29:53 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794792346 64
1794792351 64
1794792356 64
1794792361 64
1794792366 64
1794792371 64
1794792376 64
1794792381 64
1794792386 64
1794792391 64
1794792396 64
1794792401 64
1794792406 64
1794792411 64
1794792416 64
1794792421 64
1794792426 64
1794792431 64
1794792436 64
1794792441 64
```
</details>

---

