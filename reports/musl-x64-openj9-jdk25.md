---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 07:47:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1794487368 32
1794487373 32
1794487378 32
1794487383 32
1794487388 32
1794487393 32
1794487398 32
1794487403 32
1794487408 32
1794487413 32
1794487418 32
1794487423 32
1794487428 32
1794487433 11
1794487438 11
1794487443 11
1794487448 11
1794487453 11
1794487458 11
1794487463 11
```
</details>

---

