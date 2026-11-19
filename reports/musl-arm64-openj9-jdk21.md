---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 41-60 cores)</summary>

```
1795108861 46
1795108866 46
1795108871 41
1795108876 41
1795108881 41
1795108886 41
1795108891 41
1795108896 41
1795108901 41
1795108906 41
1795108911 41
1795108916 41
1795108921 41
1795108926 41
1795108931 46
1795108936 46
1795108941 46
1795108946 60
1795108951 60
1795108956 60
```
</details>

---

