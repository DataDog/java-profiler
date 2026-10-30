---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 15:32:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 10 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 13 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1793388527 47
1793388532 47
1793388537 47
1793388542 47
1793388547 47
1793388552 47
1793388557 47
1793388562 47
1793388567 47
1793388572 47
1793388577 42
1793388582 42
1793388587 42
1793388592 42
1793388597 42
1793388602 42
1793388607 42
1793388612 42
1793388617 42
1793388622 42
```
</details>

---

