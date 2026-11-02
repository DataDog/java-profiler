---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 05:56:18 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 49-52 cores)</summary>

```
1793616713 52
1793616718 52
1793616723 50
1793616728 50
1793616733 51
1793616738 51
1793616743 49
1793616748 49
1793616753 49
1793616758 49
1793616763 49
1793616768 49
1793616773 49
1793616778 49
1793616783 49
1793616788 49
1793616793 49
1793616798 51
1793616803 51
1793616808 51
```
</details>

---

