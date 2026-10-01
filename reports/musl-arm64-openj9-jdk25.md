---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 16:19:25 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1790885769 53
1790885774 53
1790885779 53
1790885784 53
1790885789 53
1790885794 53
1790885799 53
1790885804 53
1790885809 53
1790885814 48
1790885819 48
1790885824 48
1790885829 48
1790885834 48
1790885839 48
1790885844 48
1790885849 48
1790885854 48
1790885859 53
1790885864 53
```
</details>

---

