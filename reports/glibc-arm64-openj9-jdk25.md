---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-28 12:45:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777394303 64
1777394308 64
1777394313 64
1777394318 64
1777394323 64
1777394328 64
1777394333 64
1777394338 64
1777394343 64
1777394348 64
1777394353 64
1777394358 64
1777394363 64
1777394368 64
1777394373 64
1777394378 64
1777394383 64
1777394388 64
1777394393 64
1777394398 64
```
</details>

---

