---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 17:00:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1790110482 68
1790110487 68
1790110492 68
1790110497 68
1790110502 76
1790110507 76
1790110512 76
1790110517 76
1790110522 76
1790110527 76
1790110532 76
1790110537 76
1790110542 76
1790110547 76
1790110552 76
1790110557 76
1790110562 76
1790110567 76
1790110572 76
1790110577 76
```
</details>

---

