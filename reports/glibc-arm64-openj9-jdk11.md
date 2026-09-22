---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:30:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 13 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790090709 48
1790090714 48
1790090719 48
1790090724 48
1790090729 48
1790090734 48
1790090739 48
1790090744 48
1790090749 48
1790090754 48
1790090759 48
1790090764 48
1790090769 48
1790090774 48
1790090779 48
1790090784 48
1790090789 48
1790090794 48
1790090799 48
1790090804 48
```
</details>

---

