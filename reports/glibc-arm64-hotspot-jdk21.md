---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:56:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (5 unique values: 33-48 cores)</summary>

```
1793616732 33
1793616737 33
1793616742 33
1793616747 38
1793616753 38
1793616758 38
1793616763 38
1793616768 36
1793616773 36
1793616778 36
1793616783 36
1793616788 46
1793616793 46
1793616798 46
1793616803 46
1793616808 46
1793616813 48
1793616818 48
1793616823 48
1793616828 48
```
</details>

---

