---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-07 12:48:09 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1791391363 86
1791391368 86
1791391373 86
1791391378 86
1791391383 86
1791391388 86
1791391393 86
1791391398 86
1791391403 86
1791391408 86
1791391413 86
1791391418 86
1791391423 84
1791391428 84
1791391433 84
1791391438 84
1791391443 84
1791391448 84
1791391453 84
1791391458 84
```
</details>

---

