---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 13:41:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 965 |
| Sample Rate | 16.08/sec |
| Health Score | 1005% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 53-62 cores)</summary>

```
1795545456 62
1795545461 62
1795545466 62
1795545471 62
1795545477 62
1795545482 62
1795545487 62
1795545492 53
1795545497 53
1795545502 53
1795545507 53
1795545512 53
1795545517 53
1795545522 53
1795545527 53
1795545532 53
1795545537 53
1795545542 53
1795545547 53
1795545552 53
```
</details>

---

