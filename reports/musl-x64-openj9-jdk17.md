---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:12:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1793185662 43
1793185667 43
1793185672 43
1793185677 43
1793185682 43
1793185687 43
1793185692 43
1793185697 43
1793185702 43
1793185707 41
1793185712 41
1793185717 41
1793185722 41
1793185727 41
1793185732 41
1793185737 41
1793185742 43
1793185747 43
1793185752 43
1793185757 43
```
</details>

---

