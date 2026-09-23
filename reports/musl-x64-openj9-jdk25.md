---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:06:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 439 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 34-50 cores)</summary>

```
1790168530 39
1790168535 39
1790168540 39
1790168545 39
1790168550 39
1790168555 39
1790168560 39
1790168565 39
1790168570 39
1790168575 39
1790168580 39
1790168585 39
1790168590 34
1790168595 34
1790168600 50
1790168605 50
1790168610 50
1790168615 50
1790168620 48
1790168625 48
```
</details>

---

