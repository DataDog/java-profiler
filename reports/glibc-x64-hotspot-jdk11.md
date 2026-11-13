---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:36:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794594688 30
1794594693 30
1794594698 30
1794594703 30
1794594708 30
1794594713 30
1794594718 30
1794594723 30
1794594728 30
1794594733 30
1794594738 30
1794594743 30
1794594748 30
1794594753 30
1794594758 30
1794594763 30
1794594768 30
1794594773 32
1794594778 32
1794594783 32
```
</details>

---

