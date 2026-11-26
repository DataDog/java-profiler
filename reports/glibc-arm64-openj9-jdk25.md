---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 07:11:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795694868 47
1795694873 47
1795694878 47
1795694883 47
1795694888 47
1795694893 47
1795694898 47
1795694903 64
1795694908 64
1795694913 64
1795694918 64
1795694923 64
1795694928 64
1795694933 64
1795694938 64
1795694943 64
1795694948 64
1795694953 64
1795694958 64
1795694963 64
```
</details>

---

