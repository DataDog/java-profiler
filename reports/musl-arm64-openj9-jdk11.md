---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 12:41:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 964 |
| Sample Rate | 16.07/sec |
| Health Score | 1004% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793032576 48
1793032581 48
1793032586 48
1793032591 48
1793032596 48
1793032601 48
1793032606 48
1793032611 48
1793032616 48
1793032621 48
1793032626 48
1793032631 48
1793032636 48
1793032641 48
1793032646 48
1793032651 48
1793032656 48
1793032662 48
1793032667 48
1793032672 48
```
</details>

---

