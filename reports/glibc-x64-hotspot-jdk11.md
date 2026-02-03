---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:38:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 14.55/sec |
| Health Score | 909% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1770125489 32
1770125494 32
1770125499 32
1770125504 32
1770125509 32
1770125514 32
1770125519 32
1770125524 32
1770125529 32
1770125534 32
1770125539 32
1770125544 32
1770125549 32
1770125554 32
1770125559 32
1770125564 32
1770125569 32
1770125574 32
1770125579 32
1770125584 32
```
</details>

---

