---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:46:24 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 68-93 cores)</summary>

```
1794393744 93
1794393749 93
1794393754 68
1794393759 68
1794393764 68
1794393769 68
1794393774 68
1794393779 68
1794393784 68
1794393789 68
1794393794 68
1794393799 68
1794393804 68
1794393809 68
1794393814 68
1794393819 68
1794393824 68
1794393829 68
1794393834 68
1794393839 68
```
</details>

---

