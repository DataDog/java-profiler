---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 13:05:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 12 |
| Allocations | 100 |

<details>
<summary>CPU Timeline (1 unique values: 12-12 cores)</summary>

```
1793642527 12
1793642532 12
1793642537 12
1793642542 12
1793642547 12
1793642552 12
1793642557 12
1793642562 12
1793642567 12
1793642572 12
1793642577 12
1793642582 12
1793642587 12
1793642592 12
1793642597 12
1793642602 12
1793642607 12
1793642612 12
1793642617 12
1793642622 12
```
</details>

---

