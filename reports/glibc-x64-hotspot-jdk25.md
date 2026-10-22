---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:35:57 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1792675546 12
1792675551 32
1792675556 32
1792675561 32
1792675566 32
1792675571 32
1792675576 32
1792675581 32
1792675586 32
1792675591 32
1792675596 32
1792675601 32
1792675606 32
1792675611 32
1792675616 32
1792675621 32
1792675626 32
1792675631 32
1792675636 32
1792675641 32
```
</details>

---

