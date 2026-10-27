---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:58:50 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 8 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 23-36 cores)</summary>

```
1793123644 25
1793123649 25
1793123654 25
1793123659 25
1793123664 25
1793123669 25
1793123674 25
1793123679 25
1793123684 25
1793123689 25
1793123694 25
1793123699 25
1793123704 25
1793123709 25
1793123714 25
1793123719 36
1793123724 36
1793123729 23
1793123734 23
1793123739 23
```
</details>

---

