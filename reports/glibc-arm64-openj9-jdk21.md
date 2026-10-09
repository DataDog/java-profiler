---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 07:59:55 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (6 unique values: 32-44 cores)</summary>

```
1791546678 44
1791546683 44
1791546688 44
1791546693 44
1791546698 44
1791546703 44
1791546708 44
1791546713 44
1791546718 44
1791546723 44
1791546728 43
1791546733 43
1791546738 43
1791546743 43
1791546748 41
1791546753 41
1791546758 41
1791546763 41
1791546768 36
1791546773 36
```
</details>

---

