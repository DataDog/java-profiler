---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 20:50:54 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 66-78 cores)</summary>

```
1778546841 66
1778546846 66
1778546851 66
1778546856 66
1778546861 66
1778546866 66
1778546871 66
1778546876 66
1778546881 66
1778546886 66
1778546891 78
1778546896 78
1778546901 78
1778546906 78
1778546911 78
1778546916 78
1778546921 78
1778546926 78
1778546931 78
1778546936 78
```
</details>

---

