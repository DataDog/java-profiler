---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 07:16:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 12 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1786446637 64
1786446642 64
1786446647 64
1786446652 64
1786446657 64
1786446663 64
1786446668 64
1786446673 64
1786446678 64
1786446683 64
1786446688 64
1786446693 64
1786446698 64
1786446703 64
1786446708 64
1786446713 64
1786446718 64
1786446723 64
1786446728 64
1786446733 64
```
</details>

---

