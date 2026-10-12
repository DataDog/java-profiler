---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-12 04:31:35 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 14 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1791793617 48
1791793622 48
1791793627 48
1791793632 48
1791793637 48
1791793642 48
1791793647 48
1791793652 48
1791793657 48
1791793662 48
1791793667 48
1791793672 48
1791793678 48
1791793683 48
1791793688 48
1791793693 48
1791793698 48
1791793703 48
1791793708 48
1791793713 48
```
</details>

---

