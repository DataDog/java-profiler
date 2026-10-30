---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 11:23:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (5 unique values: 39-48 cores)</summary>

```
1793373512 39
1793373517 39
1793373522 39
1793373527 39
1793373532 39
1793373537 39
1793373542 39
1793373547 39
1793373552 39
1793373557 39
1793373562 41
1793373567 41
1793373572 41
1793373577 41
1793373582 41
1793373587 46
1793373592 46
1793373597 47
1793373603 47
1793373608 47
```
</details>

---

