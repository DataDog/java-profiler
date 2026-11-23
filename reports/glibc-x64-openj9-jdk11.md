---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:22:25 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 64-87 cores)</summary>

```
1795429084 87
1795429089 87
1795429094 87
1795429099 66
1795429104 66
1795429109 66
1795429114 66
1795429119 66
1795429124 66
1795429129 66
1795429134 66
1795429139 66
1795429144 66
1795429149 64
1795429154 64
1795429159 64
1795429164 64
1795429169 64
1795429174 64
1795429179 64
```
</details>

---

