---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:56:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 14 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 39-52 cores)</summary>

```
1793616748 52
1793616753 52
1793616758 52
1793616763 52
1793616768 52
1793616773 39
1793616778 39
1793616783 39
1793616788 39
1793616793 39
1793616798 39
1793616803 39
1793616808 39
1793616813 39
1793616818 39
1793616823 39
1793616828 39
1793616833 39
1793616838 39
1793616843 39
```
</details>

---

