---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 20.93/sec |
| Health Score | 1308% |
| Threads | 11 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 23.10/sec |
| Health Score | 1444% |
| Threads | 12 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (6 unique values: 35-72 cores)</summary>

```
1769702713 35
1769702718 35
1769702723 35
1769702728 37
1769702733 37
1769702738 39
1769702743 39
1769702748 39
1769702753 38
1769702758 38
1769702763 39
1769702768 39
1769702773 46
1769702778 46
1769702783 46
1769702788 46
1769702793 46
1769702798 46
1769702803 46
1769702808 46
```
</details>

---

