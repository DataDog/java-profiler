---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:30:41 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 8 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 7-11 cores)</summary>

```
1793615086 11
1793615091 7
1793615096 7
1793615101 7
1793615106 7
1793615111 7
1793615116 7
1793615121 7
1793615126 7
1793615131 7
1793615136 7
1793615141 7
1793615146 7
1793615151 7
1793615156 7
1793615161 7
1793615166 7
1793615171 7
1793615176 7
1793615181 7
```
</details>

---

