---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 06:50:15 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770119106 32
1770119111 32
1770119116 32
1770119121 32
1770119126 32
1770119131 32
1770119136 32
1770119141 27
1770119146 27
1770119151 32
1770119156 32
1770119161 32
1770119166 32
1770119171 32
1770119176 32
1770119181 32
1770119186 32
1770119191 32
1770119196 32
1770119201 32
```
</details>

---

