---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:30:19 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 7 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790090674 50
1790090679 50
1790090684 50
1790090689 50
1790090694 50
1790090699 50
1790090704 50
1790090709 50
1790090714 50
1790090719 50
1790090724 50
1790090729 50
1790090734 50
1790090739 50
1790090744 50
1790090749 50
1790090754 50
1790090759 50
1790090764 50
1790090769 50
```
</details>

---

