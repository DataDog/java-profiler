---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 07:23:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1794917985 96
1794917990 96
1794917996 96
1794918001 96
1794918006 96
1794918011 96
1794918016 96
1794918021 96
1794918026 96
1794918031 96
1794918036 96
1794918041 76
1794918046 76
1794918051 76
1794918056 76
1794918061 76
1794918066 76
1794918071 76
1794918076 76
1794918081 76
```
</details>

---

