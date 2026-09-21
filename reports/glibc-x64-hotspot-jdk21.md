---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 07:21:18 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1789989462 44
1789989467 44
1789989472 44
1789989477 44
1789989482 44
1789989487 44
1789989492 42
1789989497 42
1789989502 42
1789989507 42
1789989512 42
1789989517 42
1789989522 42
1789989527 42
1789989532 44
1789989537 44
1789989542 44
1789989547 44
1789989552 44
1789989557 44
```
</details>

---

