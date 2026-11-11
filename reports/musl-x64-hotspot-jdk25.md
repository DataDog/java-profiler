---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:35:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 21-32 cores)</summary>

```
1794396622 21
1794396627 21
1794396632 21
1794396637 30
1794396642 30
1794396647 30
1794396652 30
1794396657 30
1794396662 30
1794396667 32
1794396672 32
1794396677 32
1794396682 32
1794396687 32
1794396692 32
1794396697 32
1794396702 32
1794396707 32
1794396712 32
1794396717 32
```
</details>

---

