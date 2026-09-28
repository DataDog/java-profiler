---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 06:45:43 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 46-89 cores)</summary>

```
1790592069 46
1790592074 46
1790592079 46
1790592084 46
1790592089 46
1790592094 46
1790592099 46
1790592104 46
1790592109 46
1790592114 46
1790592119 46
1790592124 46
1790592129 61
1790592134 61
1790592139 58
1790592144 58
1790592149 58
1790592154 58
1790592159 58
1790592164 58
```
</details>

---

