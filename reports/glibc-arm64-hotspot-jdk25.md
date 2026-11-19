---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:54:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795114242 50
1795114247 50
1795114252 50
1795114257 50
1795114262 50
1795114267 50
1795114272 50
1795114277 50
1795114282 50
1795114287 50
1795114292 50
1795114297 50
1795114302 50
1795114307 50
1795114312 50
1795114317 50
1795114322 50
1795114327 50
1795114332 50
1795114337 50
```
</details>

---

