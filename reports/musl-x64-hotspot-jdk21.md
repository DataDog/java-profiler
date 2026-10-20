---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 06:11:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1792490624 15
1792490629 15
1792490634 32
1792490639 32
1792490644 32
1792490649 32
1792490654 32
1792490659 32
1792490664 32
1792490669 32
1792490674 32
1792490679 32
1792490684 32
1792490689 32
1792490694 32
1792490699 32
1792490704 32
1792490709 32
1792490714 32
1792490719 32
```
</details>

---

