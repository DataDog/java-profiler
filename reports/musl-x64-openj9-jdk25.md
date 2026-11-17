---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:58:05 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1794930709 94
1794930714 94
1794930719 94
1794930724 94
1794930729 96
1794930734 96
1794930739 96
1794930744 96
1794930749 96
1794930754 96
1794930759 96
1794930764 96
1794930769 96
1794930774 96
1794930779 96
1794930784 96
1794930789 91
1794930794 91
1794930799 91
1794930804 91
```
</details>

---

