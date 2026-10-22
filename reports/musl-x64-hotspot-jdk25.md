---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 18:25:52 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 49-55 cores)</summary>

```
1792707648 55
1792707653 55
1792707658 49
1792707663 49
1792707668 49
1792707673 49
1792707678 49
1792707683 49
1792707688 49
1792707693 49
1792707698 49
1792707703 49
1792707708 49
1792707713 49
1792707718 49
1792707723 49
1792707728 49
1792707733 49
1792707738 49
1792707743 49
```
</details>

---

