---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:56:18 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1793616698 94
1793616703 94
1793616708 94
1793616713 94
1793616718 94
1793616723 94
1793616728 92
1793616733 92
1793616738 92
1793616743 92
1793616748 92
1793616753 92
1793616758 92
1793616763 94
1793616768 94
1793616773 94
1793616778 94
1793616783 94
1793616788 94
1793616793 94
```
</details>

---

