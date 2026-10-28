---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 12:27:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 12 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793204600 46
1793204605 46
1793204611 46
1793204616 46
1793204621 46
1793204626 46
1793204631 46
1793204636 46
1793204641 46
1793204646 46
1793204651 46
1793204656 46
1793204661 46
1793204666 46
1793204671 46
1793204676 46
1793204681 51
1793204686 51
1793204691 51
1793204696 51
```
</details>

---

