---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-10 05:51:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
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
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791625602 40
1791625607 40
1791625612 40
1791625617 40
1791625622 40
1791625627 40
1791625632 40
1791625637 40
1791625642 40
1791625648 40
1791625653 40
1791625658 40
1791625663 40
1791625668 40
1791625673 40
1791625678 40
1791625683 40
1791625688 40
1791625693 40
1791625698 40
```
</details>

---

