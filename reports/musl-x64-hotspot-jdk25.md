---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-10 17:36:43 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 11 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1067 |
| Sample Rate | 17.78/sec |
| Health Score | 1111% |
| Threads | 13 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1770762502 61
1770762507 61
1770762512 61
1770762517 61
1770762522 61
1770762527 61
1770762532 61
1770762537 63
1770762542 63
1770762547 63
1770762552 63
1770762557 63
1770762562 63
1770762567 63
1770762572 63
1770762577 63
1770762582 63
1770762587 63
1770762592 63
1770762598 59
```
</details>

---

