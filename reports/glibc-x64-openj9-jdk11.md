---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 10:44:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 81-85 cores)</summary>

```
1794411581 83
1794411586 83
1794411591 83
1794411596 83
1794411601 83
1794411606 81
1794411611 81
1794411616 81
1794411621 81
1794411626 81
1794411631 81
1794411636 81
1794411641 81
1794411646 81
1794411651 81
1794411656 81
1794411661 81
1794411666 81
1794411671 83
1794411676 83
```
</details>

---

