---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:48:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794505513 64
1794505518 64
1794505523 64
1794505528 64
1794505534 64
1794505539 64
1794505544 64
1794505549 64
1794505554 64
1794505559 64
1794505564 64
1794505569 64
1794505574 51
1794505579 51
1794505584 51
1794505589 51
1794505594 51
1794505599 51
1794505604 51
1794505609 51
```
</details>

---

