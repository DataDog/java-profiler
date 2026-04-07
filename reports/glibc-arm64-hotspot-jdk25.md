---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-07 12:54:30 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775580521 64
1775580526 64
1775580531 64
1775580537 64
1775580542 64
1775580547 64
1775580552 64
1775580557 64
1775580562 64
1775580567 64
1775580572 64
1775580577 64
1775580582 64
1775580587 64
1775580592 64
1775580597 64
1775580602 64
1775580607 64
1775580612 64
1775580617 64
```
</details>

---

