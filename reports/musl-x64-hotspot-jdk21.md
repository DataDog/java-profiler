---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 19:15:10 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 10 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1793142637 96
1793142642 96
1793142647 96
1793142652 96
1793142657 96
1793142662 96
1793142667 96
1793142672 96
1793142677 96
1793142682 96
1793142687 96
1793142692 96
1793142697 96
1793142702 96
1793142707 96
1793142712 96
1793142717 96
1793142722 96
1793142727 94
1793142732 94
```
</details>

---

