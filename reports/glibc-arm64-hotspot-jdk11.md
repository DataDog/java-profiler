---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:58:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795452846 64
1795452851 64
1795452856 64
1795452861 64
1795452866 64
1795452871 59
1795452876 59
1795452881 59
1795452887 59
1795452892 59
1795452897 59
1795452902 59
1795452907 59
1795452912 59
1795452917 59
1795452922 59
1795452927 59
1795452932 59
1795452937 64
1795452942 64
```
</details>

---

