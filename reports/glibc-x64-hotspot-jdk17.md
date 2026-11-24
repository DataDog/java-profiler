---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 05:51:08 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 81-87 cores)</summary>

```
1795517189 87
1795517194 87
1795517199 87
1795517204 87
1795517209 87
1795517214 87
1795517219 87
1795517224 87
1795517229 87
1795517234 87
1795517239 87
1795517244 85
1795517249 85
1795517254 85
1795517259 85
1795517264 85
1795517269 85
1795517274 85
1795517279 85
1795517284 85
```
</details>

---

