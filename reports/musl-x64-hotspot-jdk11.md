---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-11 05:51:24 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 40-51 cores)</summary>

```
1791712021 40
1791712026 51
1791712031 51
1791712036 51
1791712041 51
1791712046 43
1791712051 43
1791712056 43
1791712061 43
1791712066 41
1791712071 41
1791712076 41
1791712081 41
1791712086 41
1791712091 41
1791712096 43
1791712101 43
1791712106 43
1791712111 43
1791712116 43
```
</details>

---

