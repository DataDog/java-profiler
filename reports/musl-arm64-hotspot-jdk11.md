---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:50:07 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 13 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 34-47 cores)</summary>

```
1794933922 34
1794933927 34
1794933932 34
1794933937 34
1794933942 34
1794933947 34
1794933952 34
1794933957 34
1794933962 34
1794933967 34
1794933972 34
1794933977 34
1794933982 34
1794933987 47
1794933992 47
1794933997 47
1794934002 47
1794934007 47
1794934012 47
1794934017 47
```
</details>

---

