---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-19 05:47:38 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 408 |

<details>
<summary>CPU Timeline (3 unique values: 91-93 cores)</summary>

```
1789811030 93
1789811035 93
1789811040 93
1789811045 93
1789811050 93
1789811055 93
1789811060 93
1789811065 93
1789811070 93
1789811075 93
1789811080 91
1789811085 91
1789811090 91
1789811095 91
1789811100 92
1789811105 92
1789811110 92
1789811115 92
1789811120 92
1789811125 92
```
</details>

---

