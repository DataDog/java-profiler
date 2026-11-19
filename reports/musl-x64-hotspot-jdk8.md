---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 12:14:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 69-77 cores)</summary>

```
1795108201 69
1795108206 69
1795108211 69
1795108216 72
1795108221 72
1795108226 72
1795108231 72
1795108236 70
1795108241 70
1795108246 70
1795108251 70
1795108256 70
1795108261 70
1795108266 70
1795108271 70
1795108277 75
1795108282 75
1795108287 75
1795108292 75
1795108297 75
```
</details>

---

