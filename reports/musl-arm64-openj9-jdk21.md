---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 13:05:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793642457 48
1793642462 48
1793642467 48
1793642472 48
1793642477 48
1793642482 48
1793642487 48
1793642492 48
1793642497 48
1793642502 48
1793642507 48
1793642512 48
1793642517 48
1793642522 48
1793642527 48
1793642532 48
1793642537 48
1793642542 48
1793642547 48
1793642552 48
```
</details>

---

