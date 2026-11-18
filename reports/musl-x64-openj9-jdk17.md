---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 61-83 cores)</summary>

```
1795010702 81
1795010707 81
1795010712 81
1795010718 81
1795010723 81
1795010728 81
1795010733 83
1795010738 83
1795010743 83
1795010748 83
1795010753 83
1795010758 83
1795010763 83
1795010768 83
1795010773 83
1795010778 83
1795010783 83
1795010788 83
1795010793 80
1795010798 80
```
</details>

---

