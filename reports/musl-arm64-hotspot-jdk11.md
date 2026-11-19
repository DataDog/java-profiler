---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:25:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1006 |
| Sample Rate | 16.77/sec |
| Health Score | 1048% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795108832 50
1795108837 50
1795108842 50
1795108847 50
1795108852 50
1795108857 50
1795108862 50
1795108867 50
1795108872 50
1795108877 50
1795108882 50
1795108887 50
1795108892 50
1795108897 50
1795108902 50
1795108907 50
1795108912 50
1795108917 50
1795108922 50
1795108927 50
```
</details>

---

