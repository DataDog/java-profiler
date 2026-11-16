---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 10:44:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1794843586 48
1794843591 48
1794843596 47
1794843601 47
1794843606 47
1794843611 47
1794843616 47
1794843621 47
1794843626 45
1794843631 45
1794843636 45
1794843641 45
1794843646 45
1794843651 45
1794843656 45
1794843661 45
1794843667 45
1794843672 45
1794843677 45
1794843682 45
```
</details>

---

