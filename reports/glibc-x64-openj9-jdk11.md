---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 03:36:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 49-52 cores)</summary>

```
1778571115 52
1778571120 52
1778571125 52
1778571130 52
1778571135 52
1778571140 52
1778571145 52
1778571150 52
1778571155 52
1778571160 52
1778571165 52
1778571170 52
1778571175 52
1778571180 52
1778571185 52
1778571190 52
1778571195 52
1778571200 52
1778571205 49
1778571210 49
```
</details>

---

