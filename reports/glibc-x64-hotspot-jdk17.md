---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:01:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 68-78 cores)</summary>

```
1794326206 71
1794326211 71
1794326216 71
1794326221 71
1794326226 71
1794326231 76
1794326236 76
1794326241 76
1794326246 76
1794326251 76
1794326256 68
1794326261 68
1794326266 68
1794326271 68
1794326276 70
1794326281 70
1794326286 70
1794326291 78
1794326296 78
1794326301 78
```
</details>

---

