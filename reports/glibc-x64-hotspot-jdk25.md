---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-24 05:38:26 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 39-46 cores)</summary>

```
1792834349 46
1792834354 44
1792834359 44
1792834364 44
1792834369 44
1792834374 44
1792834379 46
1792834384 46
1792834389 46
1792834394 46
1792834399 46
1792834404 46
1792834409 44
1792834414 44
1792834419 44
1792834424 44
1792834429 44
1792834434 39
1792834439 39
1792834444 39
```
</details>

---

