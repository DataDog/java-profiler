---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-19 08:03:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 24-31 cores)</summary>

```
1792411237 31
1792411242 31
1792411247 31
1792411252 31
1792411257 31
1792411262 31
1792411267 31
1792411272 31
1792411277 31
1792411282 31
1792411287 31
1792411292 31
1792411297 31
1792411302 31
1792411307 31
1792411312 31
1792411317 31
1792411322 31
1792411327 31
1792411332 31
```
</details>

---

