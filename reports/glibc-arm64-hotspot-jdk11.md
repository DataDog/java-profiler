---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 06:39:48 EDT

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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 934 |
| Sample Rate | 15.57/sec |
| Health Score | 973% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792406103 43
1792406108 43
1792406113 43
1792406118 43
1792406123 43
1792406128 43
1792406133 43
1792406138 43
1792406143 43
1792406148 43
1792406153 43
1792406158 48
1792406163 48
1792406168 48
1792406173 48
1792406178 48
1792406183 48
1792406188 48
1792406193 48
1792406198 48
```
</details>

---

