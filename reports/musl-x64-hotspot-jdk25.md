---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-18 13:55:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795027783 70
1795027788 70
1795027793 70
1795027798 70
1795027803 70
1795027808 70
1795027813 70
1795027818 70
1795027823 70
1795027828 70
1795027833 70
1795027838 70
1795027843 70
1795027848 70
1795027853 70
1795027858 72
1795027863 72
1795027868 72
1795027873 72
1795027878 72
```
</details>

---

