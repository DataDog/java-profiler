---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 04:59:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 83-88 cores)</summary>

```
1794477197 86
1794477202 86
1794477207 88
1794477212 88
1794477217 88
1794477222 88
1794477227 83
1794477232 83
1794477237 83
1794477242 83
1794477247 83
1794477252 83
1794477257 83
1794477262 83
1794477267 83
1794477272 83
1794477277 83
1794477282 83
1794477287 83
1794477292 83
```
</details>

---

