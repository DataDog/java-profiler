---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 09:37:46 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 95 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 49-51 cores)</summary>

```
1794839611 51
1794839616 51
1794839621 51
1794839626 51
1794839631 51
1794839636 51
1794839641 51
1794839646 50
1794839651 50
1794839656 50
1794839661 50
1794839666 50
1794839671 50
1794839676 50
1794839681 50
1794839686 50
1794839691 50
1794839696 51
1794839701 51
1794839706 51
```
</details>

---

