---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 05:49:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 74-80 cores)</summary>

```
1778579219 80
1778579224 80
1778579229 80
1778579234 80
1778579239 80
1778579244 80
1778579249 76
1778579254 76
1778579259 74
1778579264 74
1778579269 74
1778579274 74
1778579279 74
1778579284 76
1778579289 76
1778579294 76
1778579299 76
1778579304 76
1778579309 76
1778579314 76
```
</details>

---

