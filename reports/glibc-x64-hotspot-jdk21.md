---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 10:37:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 21-32 cores)</summary>

```
1790087437 22
1790087442 22
1790087447 22
1790087452 22
1790087457 22
1790087462 22
1790087467 32
1790087472 32
1790087477 32
1790087482 32
1790087487 32
1790087492 32
1790087497 32
1790087502 32
1790087507 21
1790087512 21
1790087517 21
1790087522 21
1790087527 21
1790087532 21
```
</details>

---

