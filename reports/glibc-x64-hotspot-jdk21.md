---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 11:54:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793638096 49
1793638101 49
1793638106 49
1793638111 51
1793638116 51
1793638121 51
1793638126 51
1793638131 51
1793638136 51
1793638141 51
1793638146 51
1793638151 51
1793638156 51
1793638161 51
1793638167 51
1793638172 51
1793638177 51
1793638182 51
1793638187 51
1793638192 51
```
</details>

---

