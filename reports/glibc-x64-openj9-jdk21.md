---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 05:56:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1792403470 25
1792403475 25
1792403480 25
1792403485 27
1792403490 27
1792403495 27
1792403500 32
1792403505 32
1792403510 32
1792403515 32
1792403520 32
1792403525 32
1792403530 32
1792403535 32
1792403540 32
1792403545 32
1792403550 32
1792403555 32
1792403560 32
1792403565 32
```
</details>

---

