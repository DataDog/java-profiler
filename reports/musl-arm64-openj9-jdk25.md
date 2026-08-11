---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 07:16:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1786446603 46
1786446608 46
1786446613 46
1786446618 51
1786446623 51
1786446628 51
1786446633 51
1786446638 51
1786446643 51
1786446648 51
1786446653 51
1786446658 51
1786446663 51
1786446668 51
1786446673 51
1786446678 51
1786446683 51
1786446688 51
1786446693 51
1786446698 51
```
</details>

---

