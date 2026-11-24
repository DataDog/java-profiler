---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 13:41:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 9 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 43-64 cores)</summary>

```
1795545446 43
1795545451 43
1795545456 43
1795545461 43
1795545466 43
1795545471 43
1795545476 43
1795545481 48
1795545486 48
1795545491 48
1795545496 48
1795545501 48
1795545506 48
1795545511 48
1795545516 48
1795545521 64
1795545526 64
1795545531 64
1795545536 64
1795545541 64
```
</details>

---

