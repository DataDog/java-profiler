---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 00:05:44 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 14 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795064477 44
1795064482 44
1795064487 44
1795064492 44
1795064497 44
1795064502 44
1795064507 44
1795064512 44
1795064517 44
1795064522 44
1795064527 44
1795064532 44
1795064537 44
1795064542 44
1795064547 44
1795064552 44
1795064557 44
1795064562 44
1795064567 44
1795064572 44
```
</details>

---

