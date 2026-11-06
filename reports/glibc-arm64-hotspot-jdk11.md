---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 19:52:36 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 7 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793926132 40
1793926137 40
1793926142 40
1793926147 40
1793926152 40
1793926157 40
1793926162 40
1793926167 40
1793926172 40
1793926177 40
1793926182 40
1793926187 40
1793926192 40
1793926197 40
1793926202 40
1793926207 40
1793926212 40
1793926217 40
1793926222 40
1793926227 40
```
</details>

---

