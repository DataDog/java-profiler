---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 55-62 cores)</summary>

```
1793734738 55
1793734743 55
1793734748 55
1793734753 55
1793734758 55
1793734763 55
1793734768 55
1793734773 55
1793734778 55
1793734783 55
1793734788 55
1793734793 55
1793734799 55
1793734804 60
1793734809 60
1793734814 60
1793734819 60
1793734824 60
1793734829 60
1793734834 60
```
</details>

---

