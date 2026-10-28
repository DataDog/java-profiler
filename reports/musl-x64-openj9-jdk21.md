---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:50:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1793187751 72
1793187756 72
1793187761 72
1793187766 72
1793187771 72
1793187776 72
1793187781 72
1793187786 74
1793187791 74
1793187796 74
1793187801 74
1793187806 74
1793187811 74
1793187816 74
1793187821 76
1793187826 76
1793187831 76
1793187836 76
1793187841 76
1793187846 76
```
</details>

---

