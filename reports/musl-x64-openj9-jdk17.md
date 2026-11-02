---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 06:22:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 54-79 cores)</summary>

```
1793618313 54
1793618318 79
1793618323 79
1793618328 79
1793618333 79
1793618338 79
1793618343 79
1793618348 79
1793618353 79
1793618358 79
1793618363 79
1793618368 54
1793618373 54
1793618378 54
1793618383 54
1793618388 54
1793618393 54
1793618398 54
1793618403 54
1793618408 54
```
</details>

---

