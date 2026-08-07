---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 08:27:34 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 7 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1786105415 12
1786105420 12
1786105425 12
1786105430 27
1786105435 27
1786105440 27
1786105445 27
1786105450 27
1786105455 27
1786105460 27
1786105465 27
1786105470 27
1786105475 27
1786105480 27
1786105485 27
1786105490 27
1786105495 27
1786105500 27
1786105505 27
1786105510 27
```
</details>

---

