---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 16:32:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 6 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
1795382920 33
1795382925 33
1795382930 33
1795382935 33
1795382940 33
1795382945 33
1795382950 33
1795382955 33
1795382960 33
1795382965 33
1795382970 33
1795382975 33
1795382980 33
1795382985 28
1795382990 28
1795382995 28
1795383000 28
1795383005 23
1795383010 23
1795383015 23
```
</details>

---

