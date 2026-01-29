---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 07:49:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 835 |
| Sample Rate | 27.83/sec |
| Health Score | 1739% |
| Threads | 12 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 27.90/sec |
| Health Score | 1744% |
| Threads | 13 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1769690687 92
1769690692 92
1769690697 92
1769690702 94
1769690707 94
1769690712 94
1769690717 94
1769690722 94
1769690727 94
1769690732 94
1769690737 96
1769690742 96
1769690747 96
1769690752 96
1769690757 96
1769690762 96
1769690767 96
1769690772 96
1769690777 96
1769690782 96
```
</details>

---

