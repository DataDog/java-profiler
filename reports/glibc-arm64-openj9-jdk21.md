---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 13:25:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1792689622 54
1792689627 54
1792689632 54
1792689637 54
1792689642 54
1792689647 54
1792689652 54
1792689657 54
1792689662 64
1792689667 64
1792689672 64
1792689677 64
1792689682 51
1792689687 51
1792689692 51
1792689697 51
1792689702 51
1792689707 51
1792689712 46
1792689717 46
```
</details>

---

