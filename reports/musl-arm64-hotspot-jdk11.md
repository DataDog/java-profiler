---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 07:40:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
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
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 941 |
| Sample Rate | 15.68/sec |
| Health Score | 980% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 20-48 cores)</summary>

```
1793014542 20
1793014547 20
1793014552 20
1793014557 20
1793014562 20
1793014567 20
1793014572 20
1793014577 20
1793014582 20
1793014587 20
1793014592 48
1793014597 48
1793014602 48
1793014607 48
1793014612 48
1793014617 43
1793014622 43
1793014627 43
1793014632 43
1793014637 43
```
</details>

---

