---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 05:27:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 7 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794306071 48
1794306076 48
1794306081 48
1794306086 48
1794306091 48
1794306096 48
1794306101 48
1794306106 48
1794306111 43
1794306116 43
1794306121 43
1794306126 43
1794306131 43
1794306136 43
1794306141 43
1794306146 43
1794306151 43
1794306156 43
1794306161 43
1794306166 43
```
</details>

---

