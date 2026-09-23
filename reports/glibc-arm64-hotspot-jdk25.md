---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 12:10:41 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790179517 50
1790179522 50
1790179527 50
1790179532 50
1790179537 50
1790179542 50
1790179547 50
1790179552 50
1790179557 50
1790179562 50
1790179567 50
1790179572 50
1790179577 50
1790179582 50
1790179587 50
1790179592 50
1790179597 50
1790179602 50
1790179607 50
1790179612 50
```
</details>

---

