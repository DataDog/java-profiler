---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:18:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770119050 30
1770119055 32
1770119060 32
1770119065 32
1770119070 32
1770119075 32
1770119080 32
1770119085 32
1770119090 32
1770119095 32
1770119100 32
1770119105 32
1770119110 32
1770119116 32
1770119121 32
1770119126 32
1770119131 32
1770119136 32
1770119141 32
1770119146 32
```
</details>

---

