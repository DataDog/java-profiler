---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 06:24:52 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 12 |
| Allocations | 194 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1794395942 43
1794395947 43
1794395952 43
1794395957 43
1794395962 43
1794395967 51
1794395972 51
1794395977 51
1794395982 51
1794395987 51
1794395992 51
1794395997 51
1794396002 51
1794396007 51
1794396012 51
1794396017 51
1794396022 51
1794396027 51
1794396032 51
1794396037 51
```
</details>

---

