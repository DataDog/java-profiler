---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 13:05:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 6 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793642501 48
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
1793642557 48
1793642562 48
1793642567 48
1793642572 48
1793642577 48
1793642582 48
1793642587 48
1793642592 48
1793642597 48
```
</details>

---

