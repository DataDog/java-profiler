---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 14.43/sec |
| Health Score | 902% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1769702721 43
1769702726 43
1769702731 43
1769702736 43
1769702741 43
1769702746 43
1769702751 43
1769702756 43
1769702761 43
1769702766 43
1769702771 43
1769702776 43
1769702781 43
1769702786 43
1769702791 43
1769702796 43
1769702801 43
1769702806 38
1769702811 38
1769702816 38
```
</details>

---

