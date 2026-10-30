---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 14:02:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 11 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 14 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793383151 43
1793383156 43
1793383161 43
1793383166 43
1793383171 43
1793383176 43
1793383181 43
1793383186 43
1793383191 43
1793383196 48
1793383201 48
1793383206 48
1793383211 48
1793383216 48
1793383221 48
1793383226 48
1793383231 48
1793383236 48
1793383241 48
1793383246 48
```
</details>

---

