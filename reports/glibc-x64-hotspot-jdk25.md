---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 13:05:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793642487 32
1793642492 32
1793642497 32
1793642502 32
1793642507 32
1793642512 32
1793642517 32
1793642522 32
1793642527 32
1793642532 32
1793642537 32
1793642542 32
1793642547 32
1793642552 32
1793642557 32
1793642562 32
1793642567 32
1793642572 32
1793642577 32
1793642582 32
```
</details>

---

