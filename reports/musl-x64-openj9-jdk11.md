---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:37:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 95 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 95-96 cores)</summary>

```
1789716670 96
1789716675 96
1789716680 96
1789716685 96
1789716690 96
1789716695 96
1789716700 96
1789716705 96
1789716710 96
1789716715 96
1789716720 96
1789716725 96
1789716730 96
1789716735 96
1789716740 96
1789716745 96
1789716750 96
1789716755 96
1789716760 95
1789716765 95
```
</details>

---

