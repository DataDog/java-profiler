---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 16:32:53 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 39 |
| Sample Rate | 0.65/sec |
| Health Score | 41% |
| Threads | 11 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795382935 64
1795382940 64
1795382945 64
1795382950 64
1795382955 64
1795382960 64
1795382965 64
1795382970 64
1795382975 64
1795382980 64
1795382985 64
1795382990 64
1795382995 64
1795383000 64
1795383005 64
1795383010 64
1795383015 64
1795383020 64
1795383025 64
1795383030 64
```
</details>

---

