---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 00:00:38 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 63-72 cores)</summary>

```
1795409761 63
1795409766 63
1795409771 63
1795409776 63
1795409781 63
1795409786 63
1795409791 65
1795409796 65
1795409801 65
1795409806 65
1795409811 65
1795409816 65
1795409821 65
1795409826 65
1795409831 65
1795409836 65
1795409841 63
1795409846 63
1795409851 63
1795409856 63
```
</details>

---

