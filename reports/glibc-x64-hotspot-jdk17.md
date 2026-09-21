---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 08:08:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 5 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 5-32 cores)</summary>

```
1789992196 5
1789992201 5
1789992206 5
1789992211 5
1789992216 5
1789992221 5
1789992226 5
1789992231 5
1789992236 5
1789992241 5
1789992246 5
1789992251 5
1789992256 5
1789992261 5
1789992266 5
1789992271 5
1789992276 5
1789992281 5
1789992286 5
1789992291 32
```
</details>

---

