---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 08:08:20 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1789992209 11
1789992214 11
1789992219 11
1789992224 11
1789992229 11
1789992234 11
1789992239 11
1789992244 11
1789992249 11
1789992254 11
1789992259 32
1789992264 32
1789992269 32
1789992274 32
1789992279 11
1789992284 11
1789992289 11
1789992294 11
1789992299 11
1789992304 11
```
</details>

---

