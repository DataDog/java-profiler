---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 12:33:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 40-43 cores)</summary>

```
1790699305 40
1790699310 42
1790699315 42
1790699320 42
1790699325 42
1790699330 42
1790699335 42
1790699340 42
1790699345 42
1790699350 42
1790699355 42
1790699360 42
1790699365 43
1790699370 43
1790699375 43
1790699380 43
1790699385 43
1790699390 43
1790699395 43
1790699400 43
```
</details>

---

