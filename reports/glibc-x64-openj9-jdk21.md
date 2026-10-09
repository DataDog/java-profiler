---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 07:06:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1791543757 56
1791543762 56
1791543767 56
1791543772 56
1791543777 56
1791543782 56
1791543787 56
1791543792 56
1791543797 56
1791543802 56
1791543807 56
1791543812 56
1791543817 56
1791543822 54
1791543827 54
1791543832 54
1791543837 54
1791543842 54
1791543847 54
1791543852 54
```
</details>

---

