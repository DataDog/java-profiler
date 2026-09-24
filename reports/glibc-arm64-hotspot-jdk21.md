---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:39:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (4 unique values: 42-46 cores)</summary>

```
1790238951 42
1790238956 42
1790238961 42
1790238966 42
1790238971 42
1790238976 42
1790238981 42
1790238986 42
1790238991 42
1790238996 42
1790239001 42
1790239006 42
1790239011 44
1790239016 44
1790239021 44
1790239026 44
1790239031 44
1790239036 44
1790239041 45
1790239046 45
```
</details>

---

