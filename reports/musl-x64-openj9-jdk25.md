---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 09:18:51 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 8 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794492688 32
1794492693 32
1794492698 32
1794492703 32
1794492708 32
1794492713 32
1794492718 32
1794492723 32
1794492728 32
1794492733 32
1794492738 32
1794492743 32
1794492748 32
1794492753 32
1794492758 32
1794492764 32
1794492769 32
1794492774 32
1794492779 32
1794492784 32
```
</details>

---

