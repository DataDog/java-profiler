---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:25:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 27-31 cores)</summary>

```
1795108821 27
1795108826 27
1795108831 27
1795108836 27
1795108841 27
1795108846 27
1795108851 27
1795108856 27
1795108861 28
1795108866 28
1795108871 28
1795108876 28
1795108881 28
1795108886 28
1795108891 28
1795108896 28
1795108901 31
1795108906 31
1795108911 31
1795108916 31
```
</details>

---

