---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 17:14:16 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 896 |
| Sample Rate | 14.93/sec |
| Health Score | 933% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 75-84 cores)</summary>

```
1795471741 75
1795471746 75
1795471751 75
1795471756 75
1795471761 75
1795471766 75
1795471771 75
1795471776 75
1795471781 75
1795471786 75
1795471791 75
1795471796 75
1795471801 75
1795471806 75
1795471811 75
1795471816 75
1795471821 75
1795471826 84
1795471831 84
1795471836 75
```
</details>

---

