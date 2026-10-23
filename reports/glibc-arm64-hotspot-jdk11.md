---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 16:40:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 12 |
| Allocations | 188 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792787773 43
1792787778 43
1792787783 43
1792787788 43
1792787793 43
1792787798 43
1792787803 43
1792787808 48
1792787813 48
1792787818 48
1792787823 48
1792787828 43
1792787833 43
1792787838 43
1792787843 43
1792787848 43
1792787853 43
1792787858 43
1792787863 43
1792787868 43
```
</details>

---

