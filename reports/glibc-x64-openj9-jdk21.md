---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 07:22:31 EST

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 8-32 cores)</summary>

```
1794226715 8
1794226720 8
1794226725 8
1794226730 8
1794226735 8
1794226740 8
1794226745 8
1794226750 8
1794226755 8
1794226760 8
1794226765 8
1794226770 8
1794226775 8
1794226780 8
1794226785 8
1794226790 8
1794226795 8
1794226800 32
1794226805 32
1794226810 32
```
</details>

---

