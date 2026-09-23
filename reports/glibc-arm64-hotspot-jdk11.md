---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 05:40:08 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 10 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1790156134 45
1790156139 45
1790156144 45
1790156149 45
1790156154 45
1790156159 45
1790156164 45
1790156169 45
1790156174 45
1790156179 45
1790156184 45
1790156189 45
1790156194 45
1790156199 45
1790156204 45
1790156209 45
1790156214 45
1790156219 45
1790156224 45
1790156229 48
```
</details>

---

