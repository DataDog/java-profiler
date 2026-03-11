---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 04:33:10 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 11 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 12 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 43-70 cores)</summary>

```
1773217608 47
1773217613 47
1773217618 47
1773217623 47
1773217628 43
1773217633 43
1773217638 43
1773217643 43
1773217648 43
1773217653 43
1773217658 43
1773217663 43
1773217668 43
1773217673 43
1773217678 43
1773217683 43
1773217688 43
1773217693 43
1773217698 43
1773217703 48
```
</details>

---

