---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-03 15:56:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 4 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1788465025 48
1788465030 48
1788465035 48
1788465040 48
1788465045 48
1788465050 48
1788465055 48
1788465060 48
1788465065 48
1788465070 48
1788465075 48
1788465080 48
1788465085 48
1788465090 48
1788465095 48
1788465100 48
1788465105 48
1788465110 48
1788465115 28
1788465120 28
```
</details>

---

