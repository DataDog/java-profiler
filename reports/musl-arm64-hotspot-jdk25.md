---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-21 16:58:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 41-52 cores)</summary>

```
1792615954 41
1792615959 41
1792615964 41
1792615969 41
1792615974 41
1792615979 41
1792615984 52
1792615989 52
1792615994 52
1792615999 52
1792616004 52
1792616009 52
1792616014 52
1792616019 52
1792616024 52
1792616029 52
1792616034 52
1792616039 52
1792616044 52
1792616049 52
```
</details>

---

