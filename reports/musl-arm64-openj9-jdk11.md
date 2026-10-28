---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:12:35 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1793185667 48
1793185672 43
1793185678 43
1793185683 43
1793185688 43
1793185693 43
1793185698 43
1793185703 43
1793185708 43
1793185713 43
1793185718 43
1793185723 43
1793185728 43
1793185733 43
1793185738 42
1793185743 42
1793185748 42
1793185753 42
1793185758 42
1793185763 42
```
</details>

---

