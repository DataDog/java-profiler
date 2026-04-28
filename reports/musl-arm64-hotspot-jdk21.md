---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 11:22:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1777389532 55
1777389537 55
1777389542 55
1777389547 55
1777389552 55
1777389557 55
1777389562 55
1777389567 55
1777389572 55
1777389577 60
1777389582 60
1777389587 60
1777389592 60
1777389598 60
1777389603 60
1777389608 60
1777389613 60
1777389618 60
1777389623 60
1777389628 60
```
</details>

---

