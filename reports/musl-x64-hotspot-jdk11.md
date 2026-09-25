---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:49:22 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 932 |
| Sample Rate | 15.53/sec |
| Health Score | 971% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 52-76 cores)</summary>

```
1790332967 52
1790332972 52
1790332977 52
1790332982 52
1790332987 52
1790332992 52
1790332997 52
1790333002 52
1790333007 52
1790333012 52
1790333017 52
1790333022 52
1790333027 52
1790333032 52
1790333037 52
1790333042 52
1790333047 52
1790333052 76
1790333057 76
1790333062 76
```
</details>

---

