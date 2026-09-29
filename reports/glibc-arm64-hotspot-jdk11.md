---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 05:50:05 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (7 unique values: 31-64 cores)</summary>

```
1790675072 31
1790675077 31
1790675082 31
1790675087 31
1790675092 31
1790675097 31
1790675102 41
1790675107 41
1790675112 41
1790675117 40
1790675122 40
1790675127 40
1790675132 40
1790675137 42
1790675142 42
1790675147 61
1790675152 61
1790675157 62
1790675162 62
1790675167 62
```
</details>

---

