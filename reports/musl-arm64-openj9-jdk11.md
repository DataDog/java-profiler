---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:53:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (4 unique values: 46-51 cores)</summary>

```
1794498343 46
1794498348 46
1794498353 46
1794498358 46
1794498363 46
1794498368 46
1794498373 46
1794498378 46
1794498383 46
1794498388 46
1794498393 46
1794498398 46
1794498403 46
1794498408 46
1794498413 46
1794498418 49
1794498423 49
1794498428 51
1794498433 51
1794498438 51
```
</details>

---

