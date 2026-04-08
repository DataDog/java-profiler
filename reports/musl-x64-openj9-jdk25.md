---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-08 12:51:00 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 15.35/sec |
| Health Score | 959% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 24-28 cores)</summary>

```
1775666687 28
1775666692 28
1775666697 28
1775666702 28
1775666707 28
1775666712 28
1775666717 26
1775666722 26
1775666727 26
1775666732 26
1775666737 26
1775666742 26
1775666747 26
1775666752 26
1775666757 26
1775666762 26
1775666767 24
1775666772 24
1775666777 24
1775666782 24
```
</details>

---

