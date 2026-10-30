---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:23:30 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793373487 32
1793373492 32
1793373497 32
1793373502 32
1793373507 32
1793373512 32
1793373517 32
1793373522 32
1793373527 32
1793373532 32
1793373537 32
1793373542 32
1793373547 32
1793373552 32
1793373557 32
1793373562 32
1793373567 32
1793373572 32
1793373577 32
1793373582 32
```
</details>

---

