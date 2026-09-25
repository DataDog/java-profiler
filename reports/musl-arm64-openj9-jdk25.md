---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 09:02:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790341003 48
1790341008 48
1790341013 48
1790341018 48
1790341023 48
1790341028 47
1790341033 47
1790341038 47
1790341043 47
1790341048 47
1790341053 47
1790341058 48
1790341063 48
1790341068 48
1790341073 48
1790341078 48
1790341083 48
1790341088 48
1790341093 48
1790341098 48
```
</details>

---

