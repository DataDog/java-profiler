---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 16:22:26 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (4 unique values: 55-73 cores)</summary>

```
1790713104 55
1790713109 55
1790713114 55
1790713119 55
1790713124 55
1790713129 55
1790713134 64
1790713139 64
1790713144 73
1790713149 73
1790713154 73
1790713159 73
1790713164 73
1790713169 73
1790713174 73
1790713179 73
1790713184 73
1790713189 73
1790713194 73
1790713199 73
```
</details>

---

