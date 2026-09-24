---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:39:30 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (4 unique values: 39-43 cores)</summary>

```
1790238935 39
1790238940 43
1790238945 43
1790238950 43
1790238955 40
1790238960 40
1790238965 40
1790238970 40
1790238975 40
1790238980 40
1790238985 40
1790238991 40
1790238996 40
1790239001 40
1790239006 40
1790239011 41
1790239016 41
1790239021 41
1790239026 41
1790239031 43
```
</details>

---

