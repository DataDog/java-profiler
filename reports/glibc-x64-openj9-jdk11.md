---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:10:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 57-62 cores)</summary>

```
1778090744 62
1778090749 62
1778090754 60
1778090759 60
1778090764 60
1778090769 60
1778090774 60
1778090779 60
1778090784 60
1778090789 60
1778090794 62
1778090800 62
1778090805 62
1778090810 62
1778090815 60
1778090820 60
1778090825 60
1778090830 62
1778090835 62
1778090840 57
```
</details>

---

