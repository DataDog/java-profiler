---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:48:09 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 13 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1794325474 28
1794325479 28
1794325484 28
1794325489 28
1794325494 28
1794325499 28
1794325504 28
1794325509 28
1794325514 28
1794325519 28
1794325524 64
1794325529 64
1794325534 64
1794325539 64
1794325544 28
1794325549 28
1794325554 28
1794325559 28
1794325564 28
1794325569 28
```
</details>

---

