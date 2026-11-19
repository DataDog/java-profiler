---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:28:39 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 36-75 cores)</summary>

```
1795108856 45
1795108861 45
1795108866 45
1795108871 36
1795108876 36
1795108881 36
1795108886 36
1795108891 36
1795108896 66
1795108901 66
1795108906 75
1795108911 75
1795108916 75
1795108921 75
1795108926 75
1795108931 75
1795108936 75
1795108941 75
1795108946 75
1795108951 75
```
</details>

---

