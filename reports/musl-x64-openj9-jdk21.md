---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-25 06:56:13 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 68-88 cores)</summary>

```
1792925325 84
1792925330 86
1792925335 86
1792925340 86
1792925345 86
1792925350 86
1792925355 86
1792925360 86
1792925365 86
1792925370 88
1792925375 88
1792925380 88
1792925385 88
1792925390 88
1792925395 88
1792925400 88
1792925405 88
1792925410 88
1792925415 88
1792925420 68
```
</details>

---

