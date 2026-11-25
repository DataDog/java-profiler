---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 17-48 cores)</summary>

```
1795641223 17
1795641228 17
1795641233 17
1795641238 48
1795641243 48
1795641248 48
1795641253 48
1795641259 48
1795641264 48
1795641269 48
1795641274 48
1795641279 48
1795641284 48
1795641289 48
1795641294 48
1795641299 48
1795641304 48
1795641309 48
1795641314 48
1795641319 48
```
</details>

---

