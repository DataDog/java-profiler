---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 16:36:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792614679 43
1792614684 43
1792614689 43
1792614694 43
1792614699 43
1792614704 43
1792614709 43
1792614714 43
1792614719 43
1792614724 48
1792614729 48
1792614734 48
1792614739 48
1792614744 48
1792614749 48
1792614754 48
1792614759 43
1792614764 43
1792614769 43
1792614774 43
```
</details>

---

