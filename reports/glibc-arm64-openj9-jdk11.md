---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:27:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 43-46 cores)</summary>

```
1793204571 43
1793204576 43
1793204581 43
1793204586 43
1793204591 43
1793204596 43
1793204601 43
1793204606 43
1793204611 43
1793204616 43
1793204621 43
1793204626 43
1793204631 43
1793204636 46
1793204641 46
1793204646 46
1793204651 46
1793204656 46
1793204661 46
1793204666 46
```
</details>

---

