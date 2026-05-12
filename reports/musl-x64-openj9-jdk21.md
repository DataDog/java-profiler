---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 03:57:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 42-49 cores)</summary>

```
1778572279 42
1778572284 42
1778572289 42
1778572294 42
1778572299 42
1778572304 42
1778572309 42
1778572314 42
1778572319 42
1778572324 42
1778572329 42
1778572334 42
1778572339 42
1778572344 42
1778572349 42
1778572354 42
1778572359 42
1778572364 48
1778572369 48
1778572374 47
```
</details>

---

