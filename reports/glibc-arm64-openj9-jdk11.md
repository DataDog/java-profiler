---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 09:51:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 13 |
| Allocations | 173 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1787147063 40
1787147068 40
1787147073 40
1787147078 40
1787147083 40
1787147088 40
1787147093 40
1787147098 40
1787147103 40
1787147109 40
1787147114 40
1787147119 40
1787147124 40
1787147129 40
1787147134 40
1787147139 40
1787147144 40
1787147149 40
1787147154 40
1787147159 40
```
</details>

---

