---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 11:26:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 86-94 cores)</summary>

```
1792163984 86
1792163989 86
1792163994 86
1792163999 86
1792164004 86
1792164009 94
1792164014 94
1792164019 94
1792164024 94
1792164029 91
1792164034 91
1792164039 91
1792164044 91
1792164049 91
1792164054 91
1792164059 91
1792164064 91
1792164069 91
1792164074 91
1792164079 91
```
</details>

---

