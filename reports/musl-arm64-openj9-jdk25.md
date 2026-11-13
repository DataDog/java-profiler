---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 13:48:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 12-27 cores)</summary>

```
1794595247 12
1794595252 25
1794595257 25
1794595262 25
1794595267 25
1794595272 25
1794595277 25
1794595282 25
1794595287 27
1794595292 27
1794595297 27
1794595302 27
1794595307 27
1794595312 27
1794595317 27
1794595322 27
1794595327 27
1794595332 27
1794595337 27
1794595342 27
```
</details>

---

