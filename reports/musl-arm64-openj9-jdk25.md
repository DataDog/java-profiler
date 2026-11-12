---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 11:49:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 7 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 9 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1794501729 39
1794501734 39
1794501739 39
1794501744 39
1794501749 39
1794501754 39
1794501759 39
1794501764 39
1794501769 51
1794501774 51
1794501779 51
1794501784 51
1794501789 51
1794501795 51
1794501800 51
1794501805 51
1794501810 51
1794501815 51
1794501820 51
1794501825 51
```
</details>

---

