---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 13:18:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1794420788 25
1794420793 25
1794420798 25
1794420803 25
1794420808 25
1794420813 25
1794420818 25
1794420823 25
1794420828 32
1794420833 32
1794420838 12
1794420843 12
1794420848 12
1794420853 12
1794420858 12
1794420863 12
1794420868 12
1794420873 12
1794420878 12
1794420883 12
```
</details>

---

