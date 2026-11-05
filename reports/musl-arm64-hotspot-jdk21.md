---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 09:56:10 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 43-53 cores)</summary>

```
1793890197 43
1793890202 43
1793890207 43
1793890212 43
1793890217 43
1793890222 48
1793890227 48
1793890232 48
1793890237 48
1793890242 48
1793890247 48
1793890252 48
1793890257 48
1793890262 53
1793890267 53
1793890272 53
1793890277 53
1793890282 53
1793890287 53
1793890292 53
```
</details>

---

