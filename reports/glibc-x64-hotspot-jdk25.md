---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:52:01 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 72-94 cores)</summary>

```
1794498198 94
1794498203 94
1794498208 94
1794498213 94
1794498218 94
1794498223 94
1794498228 94
1794498233 72
1794498238 72
1794498243 72
1794498248 72
1794498253 72
1794498258 74
1794498263 74
1794498268 72
1794498273 72
1794498278 72
1794498283 72
1794498288 72
1794498293 72
```
</details>

---

