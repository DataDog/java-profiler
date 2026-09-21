---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 04:48:05 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 23-32 cores)</summary>

```
1789980147 32
1789980152 32
1789980157 32
1789980162 32
1789980167 32
1789980172 32
1789980177 27
1789980182 27
1789980187 27
1789980192 23
1789980197 23
1789980202 23
1789980207 23
1789980212 23
1789980217 23
1789980222 23
1789980227 23
1789980232 23
1789980237 23
1789980242 23
```
</details>

---

