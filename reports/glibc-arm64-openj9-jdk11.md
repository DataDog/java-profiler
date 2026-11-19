---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:25:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795108856 50
1795108861 50
1795108866 50
1795108871 50
1795108876 50
1795108881 50
1795108886 50
1795108891 50
1795108896 50
1795108901 50
1795108906 50
1795108911 50
1795108916 50
1795108921 50
1795108926 50
1795108931 50
1795108936 50
1795108941 50
1795108946 50
1795108951 50
```
</details>

---

