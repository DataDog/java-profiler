---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 09:30:43 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 946 |
| Sample Rate | 15.77/sec |
| Health Score | 986% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1791293063 96
1791293068 96
1791293074 96
1791293079 96
1791293084 96
1791293089 96
1791293094 96
1791293099 96
1791293104 96
1791293109 96
1791293114 96
1791293119 96
1791293124 96
1791293129 96
1791293134 96
1791293139 96
1791293144 91
1791293149 91
1791293154 91
1791293159 91
```
</details>

---

