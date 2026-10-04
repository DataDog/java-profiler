---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-04 05:47:28 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 8 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 16-26 cores)</summary>

```
1791106988 16
1791106993 16
1791106998 16
1791107003 16
1791107008 26
1791107013 26
1791107018 26
1791107023 26
1791107028 26
1791107033 26
1791107038 26
1791107043 26
1791107048 26
1791107053 26
1791107058 26
1791107063 26
1791107068 26
1791107073 26
1791107078 26
1791107083 26
```
</details>

---

