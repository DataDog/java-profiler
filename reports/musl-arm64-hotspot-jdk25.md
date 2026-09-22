---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:27:27 EDT

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
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 41-56 cores)</summary>

```
1790093982 41
1790093987 41
1790093992 41
1790093997 41
1790094002 41
1790094007 41
1790094012 41
1790094017 41
1790094022 41
1790094027 41
1790094032 41
1790094037 41
1790094042 41
1790094047 56
1790094052 56
1790094057 56
1790094062 56
1790094067 56
1790094072 56
1790094077 56
```
</details>

---

