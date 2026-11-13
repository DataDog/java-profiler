---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:36:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1794569531 30
1794569536 30
1794569541 30
1794569546 30
1794569551 28
1794569556 28
1794569561 28
1794569566 28
1794569571 28
1794569576 28
1794569581 30
1794569586 30
1794569591 30
1794569596 30
1794569601 30
1794569606 30
1794569611 32
1794569616 32
1794569621 32
1794569626 32
```
</details>

---

