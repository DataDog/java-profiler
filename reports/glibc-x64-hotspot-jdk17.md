---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-16 12:11:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789574703 94
1789574708 94
1789574713 94
1789574718 94
1789574723 94
1789574728 94
1789574733 96
1789574738 96
1789574743 96
1789574748 96
1789574753 96
1789574758 96
1789574763 96
1789574768 96
1789574773 96
1789574778 96
1789574783 96
1789574788 96
1789574793 96
1789574798 96
```
</details>

---

