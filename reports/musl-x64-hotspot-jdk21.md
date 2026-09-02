---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-02 11:43:32 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788363608 92
1788363613 92
1788363618 92
1788363623 92
1788363628 92
1788363633 94
1788363638 94
1788363643 94
1788363648 94
1788363653 94
1788363658 94
1788363663 96
1788363668 96
1788363673 96
1788363678 96
1788363683 96
1788363688 96
1788363693 96
1788363698 96
1788363703 96
```
</details>

---

