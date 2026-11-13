---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:25:07 EST

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
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 82-94 cores)</summary>

```
1794572462 94
1794572467 94
1794572472 94
1794572477 94
1794572482 94
1794572487 94
1794572492 94
1794572497 94
1794572502 94
1794572507 94
1794572512 94
1794572517 94
1794572522 94
1794572527 87
1794572532 87
1794572537 87
1794572542 87
1794572547 82
1794572552 82
1794572557 82
```
</details>

---

