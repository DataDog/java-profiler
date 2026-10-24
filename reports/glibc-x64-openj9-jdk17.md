---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-24 04:44:31 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 61-94 cores)</summary>

```
1792831104 61
1792831109 61
1792831114 61
1792831119 61
1792831124 63
1792831129 63
1792831134 63
1792831139 63
1792831144 63
1792831149 63
1792831154 61
1792831160 61
1792831165 61
1792831170 61
1792831175 61
1792831180 61
1792831185 94
1792831190 94
1792831195 94
1792831200 94
```
</details>

---

