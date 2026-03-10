---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-10 13:55:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 72-87 cores)</summary>

```
1773165021 87
1773165026 87
1773165031 87
1773165036 87
1773165041 87
1773165046 87
1773165051 87
1773165056 87
1773165061 87
1773165066 86
1773165071 86
1773165076 86
1773165081 86
1773165086 86
1773165091 76
1773165096 76
1773165101 76
1773165106 76
1773165111 77
1773165116 77
```
</details>

---

