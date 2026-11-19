---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-19 12:14:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 12 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795108197 50
1795108202 50
1795108207 50
1795108212 50
1795108217 50
1795108222 50
1795108227 50
1795108232 50
1795108237 50
1795108242 50
1795108247 50
1795108252 50
1795108257 50
1795108262 50
1795108267 50
1795108272 50
1795108277 50
1795108282 50
1795108287 50
1795108292 50
```
</details>

---

