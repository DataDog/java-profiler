---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:50:09 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794595532 48
1794595537 48
1794595542 48
1794595547 48
1794595552 48
1794595557 48
1794595562 48
1794595567 48
1794595572 48
1794595577 48
1794595582 48
1794595587 48
1794595592 48
1794595597 48
1794595602 48
1794595607 48
1794595612 48
1794595617 48
1794595622 48
1794595627 48
```
</details>

---

