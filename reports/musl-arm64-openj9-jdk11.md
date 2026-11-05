---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 11:16:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 14 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (4 unique values: 26-61 cores)</summary>

```
1793895002 48
1793895007 48
1793895012 59
1793895017 59
1793895022 59
1793895027 59
1793895032 59
1793895037 61
1793895042 61
1793895047 61
1793895052 61
1793895057 61
1793895062 61
1793895067 61
1793895072 61
1793895077 26
1793895082 26
1793895087 26
1793895092 26
1793895097 26
```
</details>

---

