---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 22:26:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 30-34 cores)</summary>

```
1786069305 30
1786069310 30
1786069315 30
1786069320 30
1786069325 30
1786069330 30
1786069335 30
1786069340 30
1786069345 30
1786069350 30
1786069355 30
1786069360 30
1786069365 32
1786069370 32
1786069376 32
1786069381 32
1786069386 32
1786069391 32
1786069396 32
1786069401 32
```
</details>

---

