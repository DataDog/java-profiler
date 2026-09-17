---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 06:26:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 8 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1789640489 11
1789640494 11
1789640499 11
1789640504 11
1789640509 11
1789640514 11
1789640519 11
1789640524 11
1789640529 11
1789640534 11
1789640539 11
1789640544 11
1789640549 11
1789640554 11
1789640559 11
1789640564 11
1789640569 11
1789640574 11
1789640579 32
1789640584 32
```
</details>

---

