---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:25:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (4 unique values: 28-64 cores)</summary>

```
1795108829 28
1795108834 28
1795108839 28
1795108844 28
1795108849 28
1795108854 28
1795108859 28
1795108864 28
1795108869 28
1795108874 28
1795108879 42
1795108884 42
1795108889 47
1795108894 47
1795108899 64
1795108904 64
1795108909 64
1795108914 64
1795108919 64
1795108925 64
```
</details>

---

