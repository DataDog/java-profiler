---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:46:26 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794393739 32
1794393744 32
1794393749 32
1794393754 32
1794393759 32
1794393764 32
1794393769 32
1794393774 32
1794393779 32
1794393784 32
1794393789 32
1794393794 32
1794393799 32
1794393804 30
1794393809 30
1794393814 30
1794393819 30
1794393824 30
1794393829 30
1794393834 30
```
</details>

---

