---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:36:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (5 unique values: 77-96 cores)</summary>

```
1794594707 79
1794594712 79
1794594717 79
1794594722 77
1794594727 77
1794594732 77
1794594737 94
1794594742 94
1794594747 94
1794594752 94
1794594757 96
1794594762 96
1794594767 96
1794594772 96
1794594777 96
1794594782 96
1794594787 96
1794594792 96
1794594797 96
1794594802 96
```
</details>

---

