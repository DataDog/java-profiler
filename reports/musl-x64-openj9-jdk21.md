---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 14:11:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 75-79 cores)</summary>

```
1793819135 75
1793819140 75
1793819145 75
1793819150 75
1793819155 75
1793819160 79
1793819165 79
1793819170 79
1793819175 79
1793819180 79
1793819185 79
1793819190 79
1793819195 79
1793819200 79
1793819205 79
1793819210 79
1793819215 79
1793819220 79
1793819225 79
1793819230 79
```
</details>

---

