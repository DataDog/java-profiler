---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:17:45 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1794406309 42
1794406314 42
1794406319 42
1794406324 42
1794406329 42
1794406334 42
1794406339 42
1794406344 42
1794406349 42
1794406354 42
1794406359 42
1794406364 42
1794406369 42
1794406374 42
1794406379 42
1794406384 42
1794406389 42
1794406394 42
1794406399 42
1794406404 42
```
</details>

---

