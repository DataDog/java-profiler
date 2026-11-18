---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:55:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 55-90 cores)</summary>

```
1795027785 55
1795027790 55
1795027795 55
1795027800 55
1795027805 55
1795027810 55
1795027815 55
1795027820 55
1795027825 55
1795027830 55
1795027835 55
1795027840 55
1795027845 55
1795027850 64
1795027855 64
1795027860 64
1795027865 64
1795027870 73
1795027875 73
1795027880 73
```
</details>

---

