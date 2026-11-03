---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 07:41:14 EST

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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 14 |
| Allocations | 97 |

<details>
<summary>CPU Timeline (1 unique values: 28-28 cores)</summary>

```
1793709484 28
1793709489 28
1793709494 28
1793709499 28
1793709504 28
1793709509 28
1793709514 28
1793709519 28
1793709524 28
1793709529 28
1793709534 28
1793709539 28
1793709544 28
1793709549 28
1793709555 28
1793709560 28
1793709565 28
1793709570 28
1793709575 28
1793709580 28
```
</details>

---

