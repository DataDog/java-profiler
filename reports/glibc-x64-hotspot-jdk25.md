---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:23:34 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 36-56 cores)</summary>

```
1795195176 56
1795195181 56
1795195186 56
1795195191 36
1795195196 36
1795195201 36
1795195206 36
1795195211 36
1795195216 36
1795195221 36
1795195226 36
1795195231 36
1795195236 36
1795195241 36
1795195246 36
1795195251 36
1795195256 36
1795195261 36
1795195266 36
1795195271 36
```
</details>

---

