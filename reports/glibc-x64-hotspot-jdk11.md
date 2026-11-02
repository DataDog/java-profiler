---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:30:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 75-94 cores)</summary>

```
1793615066 75
1793615071 75
1793615076 77
1793615081 77
1793615086 77
1793615091 77
1793615096 77
1793615101 77
1793615106 94
1793615111 94
1793615116 94
1793615121 94
1793615126 94
1793615131 94
1793615136 94
1793615141 93
1793615146 93
1793615151 93
1793615156 93
1793615161 93
```
</details>

---

