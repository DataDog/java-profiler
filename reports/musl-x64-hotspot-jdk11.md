---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:56:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 55-74 cores)</summary>

```
1793616698 55
1793616703 55
1793616708 55
1793616713 72
1793616718 72
1793616723 72
1793616728 74
1793616733 74
1793616738 74
1793616743 74
1793616748 74
1793616753 74
1793616758 74
1793616763 74
1793616768 65
1793616773 65
1793616778 65
1793616783 65
1793616788 65
1793616793 65
```
</details>

---

