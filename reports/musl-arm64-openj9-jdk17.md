---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:25:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 13 |
| Allocations | 92 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1795108831 41
1795108836 41
1795108841 41
1795108846 41
1795108851 41
1795108856 41
1795108861 41
1795108866 41
1795108871 41
1795108876 41
1795108881 46
1795108886 46
1795108891 46
1795108896 46
1795108901 46
1795108906 46
1795108911 46
1795108916 46
1795108921 46
1795108926 46
```
</details>

---

