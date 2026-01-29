---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 22.90/sec |
| Health Score | 1431% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 37-41 cores)</summary>

```
1769702721 37
1769702726 41
1769702731 41
1769702736 41
1769702741 41
1769702746 41
1769702751 41
1769702756 41
1769702761 41
1769702766 41
1769702771 41
1769702776 41
1769702781 41
1769702786 41
1769702791 41
1769702796 41
1769702801 41
1769702806 41
1769702811 41
1769702816 41
```
</details>

---

