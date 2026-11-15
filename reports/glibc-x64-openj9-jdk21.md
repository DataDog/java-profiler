---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 08:15:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 315 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1794748211 63
1794748216 63
1794748221 63
1794748226 63
1794748231 63
1794748236 61
1794748241 61
1794748246 61
1794748251 61
1794748256 61
1794748261 61
1794748266 61
1794748271 61
1794748276 63
1794748281 63
1794748286 63
1794748291 63
1794748296 63
1794748301 63
1794748306 63
```
</details>

---

