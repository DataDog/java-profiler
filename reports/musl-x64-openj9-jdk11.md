---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:29:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (5 unique values: 40-94 cores)</summary>

```
1790238266 40
1790238271 50
1790238276 50
1790238281 50
1790238286 74
1790238291 74
1790238296 74
1790238301 74
1790238306 74
1790238311 74
1790238316 94
1790238321 94
1790238326 94
1790238331 94
1790238336 94
1790238341 94
1790238347 94
1790238352 94
1790238357 63
1790238362 63
```
</details>

---

