---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 13:05:32 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 8 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 12 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 39-40 cores)</summary>

```
1793642482 39
1793642487 39
1793642492 39
1793642497 39
1793642502 40
1793642507 40
1793642512 40
1793642517 40
1793642522 40
1793642527 40
1793642532 40
1793642537 40
1793642542 40
1793642547 40
1793642552 40
1793642557 40
1793642562 40
1793642567 40
1793642572 40
1793642577 40
```
</details>

---

