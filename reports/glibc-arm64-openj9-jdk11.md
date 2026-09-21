---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-20 21:20:05 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 12 |
| Allocations | 177 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1789953297 48
1789953302 48
1789953307 48
1789953312 48
1789953317 48
1789953322 48
1789953327 48
1789953332 48
1789953337 48
1789953342 48
1789953347 48
1789953352 48
1789953357 48
1789953362 48
1789953367 48
1789953372 48
1789953377 48
1789953382 48
1789953387 48
1789953392 48
```
</details>

---

