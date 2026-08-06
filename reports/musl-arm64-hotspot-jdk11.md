---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 08:27:25 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (4 unique values: 41-56 cores)</summary>

```
1786018977 56
1786018982 56
1786018987 56
1786018992 56
1786018997 56
1786019002 56
1786019007 56
1786019012 56
1786019017 56
1786019022 56
1786019027 46
1786019032 46
1786019037 46
1786019042 46
1786019047 41
1786019052 41
1786019057 41
1786019062 41
1786019067 41
1786019072 41
```
</details>

---

