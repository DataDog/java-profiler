---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 13:11:30 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 73-93 cores)</summary>

```
1793207227 73
1793207232 73
1793207237 93
1793207242 93
1793207247 76
1793207252 76
1793207257 76
1793207262 76
1793207267 76
1793207272 76
1793207277 76
1793207282 76
1793207287 76
1793207292 76
1793207297 76
1793207302 76
1793207307 76
1793207312 76
1793207317 76
1793207322 76
```
</details>

---

