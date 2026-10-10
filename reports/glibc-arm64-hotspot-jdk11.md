---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-10 05:51:03 EDT

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
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791625577 40
1791625582 40
1791625587 40
1791625592 40
1791625597 40
1791625602 40
1791625607 40
1791625612 40
1791625617 40
1791625622 40
1791625627 40
1791625632 40
1791625637 40
1791625642 40
1791625647 40
1791625652 40
1791625657 40
1791625662 40
1791625667 40
1791625672 40
```
</details>

---

