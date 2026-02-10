---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-10 17:36:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 12 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 55-65 cores)</summary>

```
1770762507 65
1770762512 65
1770762517 65
1770762522 65
1770762527 65
1770762532 65
1770762537 65
1770762542 65
1770762547 65
1770762552 65
1770762557 65
1770762562 65
1770762567 65
1770762572 59
1770762577 59
1770762582 59
1770762587 59
1770762592 55
1770762597 55
1770762602 55
```
</details>

---

