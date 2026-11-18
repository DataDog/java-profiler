---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 12:33:40 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795022907 51
1795022912 51
1795022917 51
1795022922 51
1795022927 51
1795022932 51
1795022937 51
1795022942 51
1795022947 51
1795022952 51
1795022957 51
1795022962 51
1795022967 51
1795022972 51
1795022977 51
1795022982 51
1795022987 51
1795022992 51
1795022997 51
1795023002 46
```
</details>

---

