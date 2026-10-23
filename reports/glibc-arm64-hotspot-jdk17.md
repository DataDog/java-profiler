---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 08:55:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 13 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792759931 38
1792759936 38
1792759941 38
1792759946 38
1792759951 38
1792759956 43
1792759961 43
1792759966 43
1792759971 43
1792759976 43
1792759981 43
1792759986 48
1792759991 48
1792759996 48
1792760001 48
1792760006 48
1792760011 48
1792760016 48
1792760021 48
1792760026 48
```
</details>

---

