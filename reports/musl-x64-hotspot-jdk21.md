---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:25:12 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 41-63 cores)</summary>

```
1792372813 42
1792372818 42
1792372823 42
1792372828 42
1792372833 42
1792372838 63
1792372843 63
1792372848 43
1792372853 43
1792372858 43
1792372863 43
1792372868 43
1792372873 41
1792372878 41
1792372883 41
1792372888 41
1792372893 41
1792372898 41
1792372903 41
1792372908 41
```
</details>

---

