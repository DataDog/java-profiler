---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:12:49 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1794931710 28
1794931715 32
1794931720 32
1794931725 32
1794931730 32
1794931735 32
1794931740 32
1794931745 32
1794931750 32
1794931755 32
1794931760 32
1794931765 32
1794931770 32
1794931775 32
1794931780 32
1794931785 32
1794931790 32
1794931795 32
1794931800 32
1794931805 28
```
</details>

---

